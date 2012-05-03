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

class LibcbioCreateDocumentTest : public ::testing::Test
{
public:
    LibcbioCreateDocumentTest() {
        // Currently we don't use the handle in the create interface
        handle = NULL;
    }

protected:
    libcbio_t handle;
};

TEST_F(LibcbioCreateDocumentTest, createEmptyDocumentWithNilPointer) {
    EXPECT_EQ(CBIO_ERROR_EINVAL,
              cbio_create_empty_document(handle, NULL));
}

TEST_F(LibcbioCreateDocumentTest, createEmptyDocument) {
    libcbio_document_t doc;
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_create_empty_document(handle, &doc));
    cbio_document_release(doc);
}

class LibcbioDocumentMemberTest : public LibcbioCreateDocumentTest
{
public:
    LibcbioDocumentMemberTest() : LibcbioCreateDocumentTest()  {
    }

    virtual void SetUp(void) {
        EXPECT_EQ(CBIO_SUCCESS,
                  cbio_create_empty_document(handle, &doc));
    }
    virtual void TearDown(void) {
        cbio_document_release(doc);
    }


protected:
    libcbio_document_t doc;
};

TEST_F(LibcbioDocumentMemberTest, setId) {
    const void *key = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_id(doc, key, 3, 0));
}

TEST_F(LibcbioDocumentMemberTest, setIdAllocate) {
    const void *key = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_id(doc, key, 3, 1));
}

TEST_F(LibcbioDocumentMemberTest, getId) {
    const void *key = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_id(doc, key, 3, 0));

    const void *stored;
    size_t nkey;
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_get_id(doc, &stored, &nkey));
    EXPECT_EQ(3, nkey);
    EXPECT_EQ(key, stored);
}

TEST_F(LibcbioDocumentMemberTest, getIdAllocated) {
    const void *key = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_id(doc, key, 3, 1));

    const void *stored;
    size_t nkey;
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_get_id(doc, &stored, &nkey));
    EXPECT_EQ(3, nkey);
    EXPECT_NE(key, stored);
}

TEST_F(LibcbioDocumentMemberTest, setMeta) {
    const void *meta = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_meta(doc, meta, 3, 0));
}

TEST_F(LibcbioDocumentMemberTest, setMetaAllocate) {
    const void *meta = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_meta(doc, meta, 3, 1));
}

TEST_F(LibcbioDocumentMemberTest, getMeta) {
    const void *meta = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_meta(doc, meta, 3, 0));

    const void *stored;
    size_t nmeta;
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_get_meta(doc, &stored, &nmeta));
    EXPECT_EQ(3, nmeta);
    EXPECT_EQ(meta, stored);
}

TEST_F(LibcbioDocumentMemberTest, getMetaAllocated) {
    const void *meta = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_meta(doc, meta, 3, 1));

    const void *stored;
    size_t nmeta;
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_get_meta(doc, &stored, &nmeta));
    EXPECT_EQ(3, nmeta);
    EXPECT_NE(meta, stored);
}

TEST_F(LibcbioDocumentMemberTest, setGetRevision) {
    for (uint64_t ii = 0; ii < 100; ++ii) {
        EXPECT_EQ(CBIO_SUCCESS,
                  cbio_document_set_revision(doc, ii));
        uint64_t rev;
        EXPECT_EQ(CBIO_SUCCESS,
                  cbio_document_get_revision(doc, &rev));
        EXPECT_EQ(ii, rev);
    }
}

TEST_F(LibcbioDocumentMemberTest, setGetDeleted) {
    for (int ii = 3; ii > -1; ii--) {
        EXPECT_EQ(CBIO_SUCCESS,
                  cbio_document_set_deleted(doc, ii));
        int deleted;
        EXPECT_EQ(CBIO_SUCCESS,
                  cbio_document_get_deleted(doc, &deleted));
        EXPECT_EQ(ii, deleted);
    }
}

TEST_F(LibcbioDocumentMemberTest, setValue) {
    const void *value = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_value(doc, value, 3, 0));
}

TEST_F(LibcbioDocumentMemberTest, setValueAllocate) {
    const void *value = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_value(doc, value, 3, 1));
}

TEST_F(LibcbioDocumentMemberTest, getValue) {
    const void *value = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_value(doc, value, 3, 0));

    const void *stored;
    size_t nvalue;
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_get_value(doc, &stored, &nvalue));
    EXPECT_EQ(3, nvalue);
    EXPECT_EQ(value, stored);
}

TEST_F(LibcbioDocumentMemberTest, getValueAllocated) {
    const void *value = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_value(doc, value, 3, 1));

    const void *stored;
    size_t nvalue;
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_get_value(doc, &stored, &nvalue));
    EXPECT_EQ(3, nvalue);
    EXPECT_NE(value, stored);
}

TEST_F(LibcbioDocumentMemberTest, getValueLengthAllocated) {
    const void *value = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_value(doc, value, 3, 1));

    size_t nvalue;
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_get_value(doc, NULL, &nvalue));
    EXPECT_EQ(3, nvalue);
}

TEST_F(LibcbioDocumentMemberTest, setGetContentType) {
    uint8_t ct = 0x0, nt;

    for (int ii = 0; ii < 0x100; ii++, ct++) {
        EXPECT_EQ(CBIO_SUCCESS,
                  cbio_document_set_content_type(doc, ct));

        EXPECT_EQ(CBIO_SUCCESS,
                  cbio_document_get_content_type(doc, &nt));

        EXPECT_EQ(ct, nt);
    }
}

TEST_F(LibcbioDocumentMemberTest, reinitialize) {

    const void *data = "foo";
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_id(doc, data, 3, 1));
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_meta(doc, data, 3, 1));
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_value(doc, data, 3, 1));
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_content_type(doc, 0x55));
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_revision(doc, 5));
    EXPECT_EQ(CBIO_SUCCESS,
              cbio_document_set_deleted(doc, 1));
    cbio_document_reinitialize(doc);
    size_t nb;

    EXPECT_EQ(CBIO_ERROR_EINVAL,
              cbio_document_get_id(doc, &data, &nb));
    EXPECT_EQ(CBIO_ERROR_EINVAL,
              cbio_document_get_meta(doc, &data, &nb));
    EXPECT_EQ(CBIO_ERROR_EINVAL,
              cbio_document_get_value(doc, &data, &nb));
    int deleted;
    EXPECT_EQ(CBIO_ERROR_EINVAL,
              cbio_document_get_deleted(doc, &deleted));
    uint64_t revno;
    EXPECT_EQ(CBIO_ERROR_EINVAL,
              cbio_document_get_revision(doc, &revno));
    uint8_t ct;
    EXPECT_EQ(CBIO_ERROR_EINVAL,
              cbio_document_get_content_type(doc, &ct));
}
