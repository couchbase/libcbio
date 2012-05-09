/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
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

#ifndef LIBCBIO_CBIO_H
#define LIBCBIO_CBIO_H 1

#include <libcbio/visibility.h>
#include <libcbio/types.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Open a handle to an instance of cbio that allows you to perform
     * various operations on a CouchDB file.
     *
     * @param name the name of the couchdb file to open. The file may
     *             be absolute or relative to the working directory of
     *             the process.
     *
     * @param mode What kind of access do we want to use?
     *             CBIO_OPEN_RDONLY opens the database in read only
     *             mode and only allows for data retrieval
     *             operations. CBIO_OPEN_RW allows for read and write
     *             operations on an <b>existing</b>
     *             database. CBIO_OPEN_CREATE allows for read and
     *             write operations and creates the database if it
     *             doesn't already exist.
     *
     * @param handle Where to store the handle upon success
     *
     * @return CBIO_SUCCESS for success, or the appropriate error code
     *                      otherwise.
     */
    LIBCBIO_API
    cbio_error_t cbio_open_handle(const char *name,
                                  libcbio_open_mode_t mode,
                                  libcbio_t *handle);

    /**
     * cbio_close_handle release all allocated resources for the handle
     * and invalidates it.
     *
     * @param handle the handle to relase
     */
    LIBCBIO_API
    void cbio_close_handle(libcbio_t handle);

    /**
     * Get the file offset of the last good header in the database file
     *
     * @param handle the handle to the database to get the offset for
     *
     * @return The offset in the file of the newest good database header
     *         block.
     */
    LIBCBIO_API
    off_t cbio_get_header_position(libcbio_t handle);

    /**
     * Create an empty document we may start to populate with values.
     *
     * @param handle Handle to the cbio instance we're going to store
     *               the document in, or NULL if we don't know. if you
     *               supply a cbio instance it may recycle old objects
     *               to allow for faster execution.
     * @param doc where to store the result
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_create_empty_document(libcbio_t handle,
                                            libcbio_document_t *doc);

    /**
     * This is a helper function to avoid having to call
     * cbio_document_release() followed by
     * cbio_create_empty_document(). Please note that you can
     * <b>not</b> call cbio_document_reinitialize() on a document
     * returned from cbio_get_document() (that have undefined behaviour,
     * but will most likely crash your process)
     *
     * @param doc the documnent to reinitialize
     */
    LIBCBIO_API
    void cbio_document_reinitialize(libcbio_document_t doc);

    /**
     * Set the documents id
     *
     * @param doc the document to update
     *
     * @param id pointer to the id. This data must be valid until
     *           the document is stored (or set allocate to 1).
     *
     * @param nid the number of bytes in the id
     *
     * @param allocate Should the library create a copy of the object
     *                 or not. Set this to 1 if the data pointed to by
     *                 id isn't going to be valid until you try to
     *                 store the object.
     *
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_set_id(libcbio_document_t doc,
                                      const void *id,
                                      size_t nid,
                                      int allocate);

    /**
     * Set the meta information for a document.
     *
     * @param doc the document to update
     *
     * @param meta pointer to the meta data to store. This data must
     *             be valid until the document is stored (or set
     *             allocate to 1).
     *
     * @param nmeta the number of bytes in the meta data
     *
     * @param allocate Should the library create a copy of the object
     *                 or not. Set this to 1 if the data pointed to by
     *                 meta isn't going to be valid until you try to
     *                 store the object.
     *
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_set_meta(libcbio_document_t doc,
                                        const void *meta,
                                        size_t nmeta,
                                        int allocate);

    /**
     * Set the documents revision number
     *
     * @param doc the document to update
     *
     * @param revno the revision number of the document
     *
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_set_revision(libcbio_document_t doc,
                                            uint64_t revno);


    /**
     * Set the documents deleted status.
     *
     * @param doc the document to update
     *
     * @param deleted set this parameter to 1 to indicate that the document
     *                is deleted
     *
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_set_deleted(libcbio_document_t doc, int deleted);

    /**
     * Set the value for a document.
     *
     * @param doc the document to update
     *
     * @param value pointer to the value to store. This data must be
     *              valid until the document is stored (or set
     *              allocate to 1).
     *
     * @param nvalue the number of bytes in the value
     *
     * @param allocate Should the library create a copy of the object
     *                 or not. Set this to 1 if the data pointed to by
     *                 value isn't going to be valid until you try to
     *                 store the object.
     *
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_set_value(libcbio_document_t doc,
                                         const void *value,
                                         size_t nvalue,
                                         int allocate);

    /**
     * Set the documents content type.
     *
     * The content type of a document describes the encoding of the data
     * to store. Currently it may be one of the following:
     * <table>
     *   <tr><th>value</th><th>description</th><tr>
     *   <tr>
     *     <td>CBIO_DOC_IS_COMPRESSED</td>
     *     <td>Document contents compressed via Snappy</td>
     *   </tr>
     *   <tr>
     *     <td>CBIO_DOC_IS_JSON</td>
     *     <td>Document is valid JSON data</td>
     *   </tr>
     *   <tr>
     *     <td>CBIO_DOC_INVALID_JSON</td>
     *     <td>Document was checked, and was not valid JSON</td>
     *   </tr>
     *   <tr>
     *     <td>CBIO_DOC_INVALID_JSON_KEY</td>
     *     <td>Document was checked, and contained reserved keys,
     *         was not inserted as JSON.</td>
     *   </tr>
     *   <tr>
     *     <td>CBIO_DOC_NON_JSON_MODE</td>
     *     <td>Document was not checked (DB running in non-JSON mode)</td>
     *   </tr>
     * </table>
     *
     *
     * @param doc the document to update
     *
     * @param content_type The content type.
     *
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_set_content_type(libcbio_document_t doc,
                                                uint8_t content_type);


    /**
     * Get a documents id
     *
     * Please note that the values returned points to the data inside
     * the document and will be invalidated as soon as the docment is
     * invalidated.
     *
     * @param doc the document to get the id from
     * @param id where to store the pointer to the id
     * @param nid the number of bytes in the id
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_get_id(libcbio_document_t doc,
                                      const void **id,
                                      size_t *nid);

    /**
     * Get a documents meta data
     *
     * Please note that the values returned points to the data inside
     * the document and will be invalidated as soon as the docment is
     * invalidated.
     *
     * @param doc the document to get the meta data from
     * @param meta where to store the pointer to the meta data
     * @param nmeta the number of bytes in the meta data
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_get_meta(libcbio_document_t doc,
                                        const void **meta,
                                        size_t *nmeta);

    /**
     * Get a documents revision
     *
     * @param doc the document to get the revision from
     * @param revno where to store the revision number
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_get_revision(libcbio_document_t doc,
                                            uint64_t *revno);


    /**
     * Get a documents deleted flag
     *
     * @param doc the document to get the deletion flag from
     * @param deleted where to store the deletion flag
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_get_deleted(libcbio_document_t doc,
                                           int *deleted);

    /**
     * Get a documents value
     *
     * Please note that the values returned points to the data inside
     * the document and will be invalidated as soon as the docment is
     * invalidated.
     *
     * @param doc the document to get the value from
     * @param value where to store the pointer to the value
     * @param value the number of bytes in the value
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_get_value(libcbio_document_t doc,
                                         const void **value,
                                         size_t *nvalue);

    /**
     * Get a documents content type
     *
     * @param doc the document to get the content type from
     * @param content_type where to store the content type
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_document_get_content_type(libcbio_document_t doc,
                                                uint8_t *content_type);

    /**
     * Get a document identified by id from the couch database.
     *
     * A document returned from this method must be released by calling
     * cbio_document_release.
     *
     * Please note that this method will <b>not</b> return deleted
     * documents. In order to get a deleted document you need to call
     * cbio_get_document_ex.
     *
     * @param handle the cbio instance to get the document from
     * @param id the identifier of the document to search for
     * @param nid the number of bytes in the identifier
     * @param doc where to store the result.
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_get_document(libcbio_t handle,
                                   const void *id,
                                   size_t nid,
                                   libcbio_document_t *doc);

    /**
     * Get a document (possibly deleted) identified by id from the
     * couch database.
     *
     * The only difference between this method and cbio_get_document
     * is that this method allows you to get deleted documents.
     *
     * @param handle the cbio instance to get the document from
     * @param id the identifier of the document to search for
     * @param nid the number of bytes in the identifier
     * @param doc where to store the result.
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_get_document_ex(libcbio_t handle,
                                      const void *id,
                                      size_t nid,
                                      libcbio_document_t *doc);


    /**
     * Store a single document in the couch database
     *
     * @param handle the cbio instance to store the document to
     * @param doc the document to store
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_store_document(libcbio_t handle,
                                     libcbio_document_t doc);

    /**
     * Store a batch of documents couch database
     *
     * @param handle the cbio instance to store the documents to
     * @param doc pointer to an array of documents
     * @param ndocs the number of elements in the array
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_store_documents(libcbio_t handle,
                                      libcbio_document_t *doc,
                                      size_t ndocs);
    /**
     * Notify cbio that the document is no longer in use and that it's
     * resources may be reused/released.
     *
     * @param doc the document to release
     */
    LIBCBIO_API
    void cbio_document_release(libcbio_document_t doc);

    /**
     * Commit all (pending) operations to disk
     *
     * @param handle the cbio instance to complete and commit all operations for
     * @return CBIO_SUCCESS upon success, or an appropriate error code
     *                      describing the problem.
     */
    LIBCBIO_API
    cbio_error_t cbio_commit(libcbio_t handle);

    /**
     * Convert an error code to a human readable string
     *
     * @param err the error code to translate
     * @return A pointer to a null terminated string describing the error.
     *         Do <b>NOT</b> try to modify or release this string
     */
    LIBCBIO_API
    const char *cbio_strerror(cbio_error_t err);

    /**
     * The callback function used by cbio_changes_since() to iterate
     * through the documents.
     *
     * The document automatically released if the callback
     * returns 0. A non-zero return value will preserve the document
     * for future use (should be freed with cbio_document_release() by the
     * caller)
     *
     * @param habdle the libcbio handle
     * @param doc the current document
     * @param ctx user context
     * @return 0 or 1. See description above
     */
    typedef int (*cbio_changes_callback_fn)(libcbio_t handle,
                                            libcbio_document_t doc,
                                            void *ctx);

    /**
     * Iterate through the changes since sequence number `since`.
     *
     * @param handle libcbio handle
     * @param since the sequence number to start iterating from
     * @param callback the callback function used to iterate over all changes
     * @param ctx client context (passed to the callback)
     * @return CBIO_SUCCESS upon success
     */
    LIBCBIO_API
    cbio_error_t cbio_changes_since(libcbio_t handle,
                                    uint64_t since,
                                    cbio_changes_callback_fn callback,
                                    void *ctx);

#ifdef __cplusplus
}
#endif

#endif
