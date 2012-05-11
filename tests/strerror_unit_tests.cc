/* -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 *     Copyright 2012 Couchbase, Inc.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include <libcbio/cbio.h>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <gtest/gtest.h>

using namespace std;

class LibcbioStrerrorTest : public ::testing::Test
{
public:

protected:
};

TEST_F(LibcbioStrerrorTest, testKnownErrorCodes) {
    EXPECT_STREQ("success", cbio_strerror(CBIO_SUCCESS));
    EXPECT_STREQ("allocation failed", cbio_strerror(CBIO_ERROR_ENOMEM));
    EXPECT_STREQ("io error", cbio_strerror(CBIO_ERROR_EIO));
    EXPECT_STREQ("invalid arguments", cbio_strerror(CBIO_ERROR_EINVAL));
    EXPECT_STREQ("Internal error", cbio_strerror(CBIO_ERROR_INTERNAL));
    EXPECT_STREQ("failed to open file", cbio_strerror(CBIO_ERROR_OPEN_FILE));
    EXPECT_STREQ("file corrupt", cbio_strerror(CBIO_ERROR_CORRUPT));
    EXPECT_STREQ("no entry", cbio_strerror(CBIO_ERROR_ENOENT));
    EXPECT_STREQ("no header", cbio_strerror(CBIO_ERROR_NO_HEADER));
    EXPECT_STREQ("illegal header version",
                 cbio_strerror(CBIO_ERROR_HEADER_VERSION));
    EXPECT_STREQ("checksum fail", cbio_strerror(CBIO_ERROR_CHECKSUM_FAIL));
}

TEST_F(LibcbioStrerrorTest, testUnknownErrorCodes) {

    for (int ii = -200; ii < 200; ++ii) {
        if (ii < static_cast<int>(CBIO_SUCCESS) &&
            ii > static_cast<int>(CBIO_ERROR_CHECKSUM_FAIL)) {
            EXPECT_STREQ("Internal error",
                         cbio_strerror(static_cast<cbio_error_t>(ii)));
        }
    }
}
