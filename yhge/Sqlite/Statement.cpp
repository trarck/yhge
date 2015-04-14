
#include "Statement.h"

#include "SqliteDriver.h"
#include "Column.h"


NS_CC_YHGE_SQLITE_BEGIN

// Compile and register the SQL query for the provided SQLite Database Connection
Statement::Statement(SqliteDriver &driver, const char* query) : // throw(SQLite::Exception)
    _query(query),
    _stmtPtr(driver.getDB(), _query), // prepare the SQL query, and ref count (needs Database friendship)
    _columnCount(0),
    _ok(false),
    _done(false)
{
    _columnCount = sqlite3_column_count(_stmtPtr);
}

// Compile and register the SQL query for the provided SQLite Database Connection
Statement::Statement(SqliteDriver &driver, const std::string& query) : // throw(SQLite::Exception)
    _query(query),
    _stmtPtr(driver.getDB(), _query), // prepare the SQL query, and ref count (needs Database friendship)
    _columnCount(0),
    _ok(false),
    _done(false)
{
    _columnCount = sqlite3_column_count(_stmtPtr);
}

// Finalize and unregister the SQL query from the SQLite Database Connection.
Statement::~Statement(void) // nothrow
{
    // the finalization will be done by the destructor of the last shared pointer
}

// Reset the statement to make it ready for a new execution
void Statement::reset(void) // throw(SQLite::Exception)
{
    _ok = false;
    _done = false;
    int ret = sqlite3_reset(_stmtPtr);
    check(ret);
}

// Bind an int value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const int index, const int& value) // throw(SQLite::Exception)
{
    int ret = sqlite3_bind_int(_stmtPtr, index, value);
    check(ret);
}

// Bind a 64bits int value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const int index, const sqlite3_int64& value) // throw(SQLite::Exception)
{
    int ret = sqlite3_bind_int64(_stmtPtr, index, value);
    check(ret);
}

// Bind a double (64bits float) value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const int index, const double& value) // throw(SQLite::Exception)
{
    int ret = sqlite3_bind_double(_stmtPtr, index, value);
    check(ret);
}

// Bind a string value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const int index, const std::string& value) // throw(SQLite::Exception)
{
    int ret = sqlite3_bind_text(_stmtPtr, index, value.c_str(), static_cast<int>(value.size()), SQLITE_TRANSIENT);
    check(ret);
}

// Bind a text value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const int index, const char* apValue) // throw(SQLite::Exception)
{
    int ret = sqlite3_bind_text(_stmtPtr, index, apValue, -1, SQLITE_TRANSIENT);
    check(ret);
}

// Bind a binary blob value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const int index, const void* apValue, const int aSize) // throw(SQLite::Exception)
{
    int ret = sqlite3_bind_blob(_stmtPtr, index, apValue, aSize, SQLITE_TRANSIENT);
    check(ret);
}

// Bind a NULL value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const int index) // throw(SQLite::Exception)
{
    int ret = sqlite3_bind_null(_stmtPtr, index);
    check(ret);
}


// Bind an int value to a parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const char* name, const int& value) // throw(SQLite::Exception)
{
    int index = sqlite3_bind_parameter_index(_stmtPtr, name);
    int ret   = sqlite3_bind_int(_stmtPtr, index, value);
    check(ret);
}

// Bind a 64bits int value to a parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const char* name, const sqlite3_int64& value) // throw(SQLite::Exception)
{
    int index = sqlite3_bind_parameter_index(_stmtPtr, name);
    int ret   = sqlite3_bind_int64(_stmtPtr, index, value);
    check(ret);
}

// Bind a double (64bits float) value to a parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const char* name, const double& value) // throw(SQLite::Exception)
{
    int index = sqlite3_bind_parameter_index(_stmtPtr, name);
    int ret   = sqlite3_bind_double(_stmtPtr, index, value);
    check(ret);
}

// Bind a string value to a parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const char* name, const std::string& value) // throw(SQLite::Exception)
{
    int index = sqlite3_bind_parameter_index(_stmtPtr, name);
    int ret   = sqlite3_bind_text(_stmtPtr, index, value.c_str(), static_cast<int>(value.size()), SQLITE_TRANSIENT);
    check(ret);
}

// Bind a text value to a parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const char* name, const char* apValue) // throw(SQLite::Exception)
{
    int index = sqlite3_bind_parameter_index(_stmtPtr, name);
    int ret   = sqlite3_bind_text(_stmtPtr, index, apValue, -1, SQLITE_TRANSIENT);
    check(ret);
}

// Bind a binary blob value to a parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const char* name, const void* apValue, const int aSize) // throw(SQLite::Exception)
{
    int index = sqlite3_bind_parameter_index(_stmtPtr, name);
    int ret   = sqlite3_bind_blob(_stmtPtr, index, apValue, aSize, SQLITE_TRANSIENT);
    check(ret);
}

// Bind a NULL value to a parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement
void Statement::bind(const char* name) // throw(SQLite::Exception)
{
    int index = sqlite3_bind_parameter_index(_stmtPtr, name);
    int ret   = sqlite3_bind_null(_stmtPtr, index);
    check(ret);
}


// Execute a step of the query to fetch one row of results
bool Statement::executeStep(void) // throw(SQLite::Exception)
{
    if (false == _done)
    {
        int ret = sqlite3_step(_stmtPtr);
        if (SQLITE_ROW == ret) // one row is ready : call getColumn(N) to access it
        {
            _ok = true;
        }
        else if (SQLITE_DONE == ret) // no (more) row ready : the query has finished executing
        {
            _ok = false;
            _done = true;
        }
        else
        {
            _ok = false;
            _done = false;
            CCLOGERROR("Statement::executeStep err:%s",sqlite3_errmsg(_stmtPtr));
        }
    }
    else
    {
        CCLOGERROR("Statement need to be reseted");
    }

    return _ok; // true only if one row is accessible by getColumn(N)
}

// Execute a one-step query with no expected result
int Statement::execute(void) // throw(SQLite::Exception)
{
    if (false == _done)
    {
        int ret = sqlite3_step(_stmtPtr);
        if (SQLITE_DONE == ret) // the statement has finished executing successfully
        {
            _ok = false;
            _done = true;
        }
        else if (SQLITE_ROW == ret)
        {
            _ok = false;
            _done = false;
            CCLOGERROR("exec() does not expect results");
        }
        else
        {
            _ok = false;
            _done = false;
            CCLOGERROR("Statement::exec err:%s",sqlite3_errmsg(_stmtPtr));
        }
    }
    else
    {
        CCLOGERROR("Statement need to be reseted");
    }

    // Return the number of rows modified by those SQL statements (INSERT, UPDATE or DELETE)
    return sqlite3_changes(_stmtPtr);
}

// Return a copy of the column data specified by its index starting at 0
// (use the Column copy-constructor)
Column Statement::getColumn(const int index) // throw(SQLite::Exception)
{
    CCAssert(true==_ok, "No row to get a column from");
    CCAssert(index >=0 && index < _columnCount, "Column index out of range");

    // Share the Statement Object handle with the new Column created
    return Column(_stmtPtr, index);
}

//get column pointer,muse delele by call
void  Statement::getColumn(const int index,Column** column)
{
    CCAssert(true==_ok, "No row to get a column from");
    CCAssert(index >=0 && index < _columnCount, "Column index out of range");
    
    *column=new Column(_stmtPtr,index);
}

// Test if the column is NULL
bool Statement::isColumnNull(const int index) const // throw(SQLite::Exception)
{
    if (false == _ok)
    {
        CCLOGERROR("No row to get a column from");
    }
    else if ((index < 0) || (index >= _columnCount))
    {
        CCLOGERROR("Column index out of range");
    }

    return (SQLITE_NULL == sqlite3_column_type(_stmtPtr, index));
}

// Check if aRet equal SQLITE_OK, else throw a SQLite::Exception with the SQLite error message
void Statement::check(const int aRet) const // throw(SQLite::Exception)
{
    if (SQLITE_OK != aRet)
    {
        CCLOGERROR("%s",sqlite3_errmsg(_stmtPtr));
    }
}


////////////////////////////////////////////////////////////////////////////////
// Internal class : shared pointer to the sqlite3_stmt SQLite Statement Object
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Prepare the statement and initialize its reference counter
 *
 * @param[in] apSQLite  The sqlite3 database connexion
 * @param[in] aQuery    The SQL query string to prepare
 */
Statement::Ptr::Ptr(sqlite3* apSQLite, std::string& aQuery) :
    _db(apSQLite),
    _stmt(NULL),
    _refCount(NULL)
{
    int ret = sqlite3_prepare_v2(apSQLite, aQuery.c_str(), static_cast<int>(aQuery.size()), &_stmt, NULL);
    if (SQLITE_OK != ret)
    {
        CCLOGERROR("%s",sqlite3_errmsg(_db));
    }
    // Initialize the reference counter of the sqlite3_stmt :
    // used to share the _stmtPtr between Statement and Column objects;
    // This is needed to enable Column objects to live longer than the Statement objet it refers to.
    _refCount = new unsigned int(1);
}

/**
 * @brief Copy constructor increments the ref counter
 *
 * @param[in] aPtr Pointer to copy
 */
Statement::Ptr::Ptr(const Statement::Ptr& aPtr) :
    _db(aPtr._db),
    _stmt(aPtr._stmt),
    _refCount(aPtr._refCount)
{
    assert(NULL != _refCount);
    assert(0 != *_refCount);

    // Increment the reference counter of the sqlite3_stmt,
    // asking not to finalize the sqlite3_stmt during the lifetime of the new objet
    ++(*_refCount);
}

/**
 * @brief Decrement the ref counter and finalize the sqlite3_stmt when it reaches 0
 */
Statement::Ptr::~Ptr(void) throw() // nothrow
{
    assert(NULL != _refCount);
    assert(0 != *_refCount);

    // Decrement and check the reference counter of the sqlite3_stmt
    --(*_refCount);
    if (0 == *_refCount)
    {
        // If count reaches zero, finalize the sqlite3_stmt,
        // as no Statement not Column objet use it anymore
        int ret = sqlite3_finalize(_stmt);
        // Never throw an exception in a destructor
        CCAssert(SQLITE_OK == ret, sqlite3_errmsg(_db));  // See SQLITECPP_ENABLE_ASSERT_HANDLER

        // and delete the reference counter
        delete _refCount;
        _refCount = NULL;
        _stmt = NULL;
    }
    // else, the finalization will be done later, by the last object
}

NS_CC_YHGE_SQLITE_END
