#ifndef YHGE_SQLITE_STATEMENT_H_
#define YHGE_SQLITE_STATEMENT_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <sqlite3.h>
#include <string>
#include "SqliteMacros.h"

NS_CC_YHGE_SQLITE_BEGIN

// Forward declaration
class SqliteDriver;
class Column;

/**
 * @brief RAII encapsulation of a prepared SQLite Statement.
 *
 * A Statement is a compiled SQL query ready to be executed step by step
 * to provide results one row at a time.
 *
 * Resource Acquisition Is Initialization (RAII) means that the Statement
 * is compiled in the constructor and finalized in the destructor, so that there is
 * no need to worry about memory management or the validity of the underlying SQLite Statement.
 *
 * Thread-safety: a Statement object shall not be shared by multiple threads, because :
 * 1) in the SQLite "Thread Safe" mode, "SQLite can be safely used by multiple threads
 *    provided that no single database connection is used simultaneously in two or more threads."
 * 2) the SQLite "Serialized" mode is not supported by SQLiteC++,
 *    because of the way it shares the underling SQLite precompiled statement
 *    in a custom shared pointer (See the inner class "Statement::Ptr").
 */
class Statement
{
public:
    class Ptr;

    /**
     * @brief Compile and register the SQL query for the provided SQLite Database Connection
     *
     * @param[in] database the SQLite Database Connection
     * @param[in] query   an UTF-8 encoded query string
     *
     * Exception is thrown in case of error, then the Statement object is NOT constructed.
     */
    Statement(SqliteDriver& driver, const char* query); // throw(SQLite::Exception);

    /**
     * @brief Compile and register the SQL query for the provided SQLite Database Connection
     *
     * @param[in] database the SQLite Database Connection
     * @param[in] query    an UTF-8 encoded query string
     *
     * Exception is thrown in case of error, then the Statement object is NOT constructed.
     */
    Statement(SqliteDriver& driver, const std::string& query); // throw(SQLite::Exception);

    /**
     * @brief Finalize and unregister the SQL query from the SQLite Database Connection.
     */
    virtual ~Statement(void); // nothrow

    /**
     * @brief Reset the statement to make it ready for a new execution.
     */
    void reset(void); // throw(SQLite::Exception);

    ////////////////////////////////////////////////////////////////////////////
    // Bind a value to a parameter of the SQL statement,
    // in the form "?" (unnamed), "?NNN", ":VVV", "@VVV" or "$VVV".
    //
    // Can use the parameter index, starting from "1", to the higher NNN value,
    // or the complete parameter name "?NNN", ":VVV", "@VVV" or "$VVV"
    // (prefixed with the corresponding sign "?", ":", "@" or "$")
    //
    // Note that for text and blob values, the SQLITE_TRANSIENT flag is used,
    // which tell the sqlite library to make its own copy of the data before the bind() call returns.
    // This choice is done to prevent any common misuses, like passing a pointer to a 
    // dynamic allocated and temporary variable (a std::string for instance).
    // This is under-optimized for static data (a static text define in code)
    // as well as for dynamic allocated buffer which could be transfer to sqlite
    // instead of being copied.

    /**
     * @brief Bind an int value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    void bind(const int index, const int&           value)  ; // throw(SQLite::Exception);
    /**
     * @brief Bind a 64bits int value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    void bind(const int index, const sqlite3_int64& value)  ; // throw(SQLite::Exception);
    /**
     * @brief Bind a double (64bits float) value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    void bind(const int index, const double&        value)  ; // throw(SQLite::Exception);
    /**
     * @brief Bind a string value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     *
     * @note This uses the SQLITE_TRANSIENT flag, making a copy of the data, for SQLite internal use
     */
    void bind(const int index, const std::string&   value)  ; // throw(SQLite::Exception);
    /**
     * @brief Bind a text value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     *
     * @note This uses the SQLITE_TRANSIENT flag, making a copy of the data, for SQLite internal use
     */
    void bind(const int index, const char*          value) ; // throw(SQLite::Exception);
    /**
     * @brief Bind a binary blob value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     *
     * @note This uses the SQLITE_TRANSIENT flag, making a copy of the data, for SQLite internal use
     */
    void bind(const int index, const void*          value, const int aSize) ; // throw(SQLite::Exception);
    /**
     * @brief Bind a NULL value to a parameter "?", "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    void bind(const int index); // throw(SQLite::Exception);

    /**
     * @brief Bind an int value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    void bind(const char* name, const int&            value)  ; // throw(SQLite::Exception);
    /**
     * @brief Bind a 64bits int value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    void bind(const char* name, const sqlite3_int64&  value)  ; // throw(SQLite::Exception);
    /**
     * @brief Bind a double (64bits float) value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    void bind(const char* name, const double&         value)  ; // throw(SQLite::Exception);
    /**
     * @brief Bind a string value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     *
     * @note This uses the SQLITE_TRANSIENT flag, making a copy of the data, for SQLite internal use
     */
    void bind(const char* name, const std::string&    value)  ; // throw(SQLite::Exception);
    /**
     * @brief Bind a text value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     *
     * @note This uses the SQLITE_TRANSIENT flag, making a copy of the data, for SQLite internal use
     */
    void bind(const char* name, const char*           value) ; // throw(SQLite::Exception);
    /**
     * @brief Bind a binary blob value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     *
     * @note This uses the SQLITE_TRANSIENT flag, making a copy of the data, for SQLite internal use
     */
    void bind(const char* name, const void*           value, const int aSize) ; // throw(SQLite::Exception);
    /**
     * @brief Bind a NULL value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    void bind(const char* name); // throw(SQLite::Exception); // bind NULL value


    /**
     * @brief Bind an int value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    inline void bind(const std::string& name, const int&            value) // throw(SQLite::Exception);
    {
        bind(name.c_str(), value);
    }
    /**
     * @brief Bind a 64bits int value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    inline void bind(const std::string& name, const sqlite3_int64&  value) // throw(SQLite::Exception);
    {
        bind(name.c_str(), value);
    }
    /**
     * @brief Bind a double (64bits float) value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    inline void bind(const std::string& name, const double&         value) // throw(SQLite::Exception);
    {
        bind(name.c_str(), value);
    }
    /**
     * @brief Bind a string value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     *
     * @note This uses the SQLITE_TRANSIENT flag, making a copy of the data, for SQLite internal use
     */
    inline void bind(const std::string& name, const std::string&    value) // throw(SQLite::Exception);
    {
        bind(name.c_str(), value);
    }
    /**
     * @brief Bind a text value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     *
     * @note This uses the SQLITE_TRANSIENT flag, making a copy of the data, for SQLite internal use
     */
    inline void bind(const std::string& name, const char*           value) // throw(SQLite::Exception);
    {
        bind(name.c_str(), value);
    }
    /**
     * @brief Bind a binary blob value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     *
     * @note This uses the SQLITE_TRANSIENT flag, making a copy of the data, for SQLite internal use
     */
    inline void bind(const std::string& name, const void*           value, const int aSize) // throw(SQLite::Exception);
    {
        bind(name.c_str(), value, aSize);
    }
    /**
     * @brief Bind a NULL value to a named parameter "?NNN", ":VVV", "@VVV" or "$VVV" in the SQL prepared statement (index >= 1)
     */
    inline void bind(const std::string& name) // throw(SQLite::Exception); // bind NULL value
    {
        bind(name.c_str());
    }


    ////////////////////////////////////////////////////////////////////////////

    /**
     * @brief Execute a step of the prepared query to fetch one row of results.
     *
     *  While true is returned, a row of results is available, and can be accessed
     * thru the getColumn() method
     *
     * @see exec() execute a one-step prepared statement with no expected result
     * @see Database::exec() is a shortcut to execute one or multiple statements without results
     *
     * @return - true  (SQLITE_ROW)  if there is another row ready : you can call getColumn(N) to get it
     *                               then you have to call executeStep() again to fetch more rows until the query is finished
     *         - false (SQLITE_DONE) if the query has finished executing : there is no (more) row of result
     *                               (case of a query with no result, or after N rows fetched successfully)
     *
     * @throw SQLite::Exception in case of error
     */
    bool executeStep(void); // throw(SQLite::Exception);

    /**
     * @brief Execute a one-step query with no expected result.
     *
     *  This method is useful for any kind of statements other than the Data Query Language (DQL) "SELECT" :
     *  - Data Definition Language (DDL) statements "CREATE", "ALTER" and "DROP"
     *  - Data Manipulation Language (DML) statements "INSERT", "UPDATE" and "DELETE"
     *  - Data Control Language (DCL) statements "GRANT", "REVOKE", "COMMIT" and "ROLLBACK"
     *
     * It is similar to Database::exec(), but using a precompiled statement, it adds :
     * - the ability to bind() arguments to it (best way to insert data),
     * - reusing it allows for better performances (efficient for multiple insertion).
     *
     * @see executeStep() execute a step of the prepared query to fetch one row of results
     * @see Database::exec() is a shortcut to execute one or multiple statements without results
     *
     * @return number of row modified by this SQL statement (INSERT, UPDATE or DELETE)
     *
     * @throw SQLite::Exception in case of error, or if row of results are returned !
     */
    int execute(void); // throw(SQLite::Exception);

    ////////////////////////////////////////////////////////////////////////////

    /**
     * @brief Return a copie of the column data specified by its index
     *
     *  Can be used to access the data of the current row of result when applicable,
     * while the executeStep() method returns true.
     *
     *  Throw an exception if there is no row to return a Column from :
     * - before any executeStep() call
     * - after the last executeStep() returned false
     * - after a reset() call
     *
     *  Throw an exception if the specified index is out of the [0, getColumnCount()) range.
     *
     * @param[in] index    Index of the column, starting at 0
     *
     * @note    This method is no more const, starting in v0.5,
     *          which reflects the fact that the returned Column object will
     *          share the ownership of the underlying sqlite3_stmt.
     *
     * @warning The resulting Column object must not be memorized "as-is".
     *          Is is only a wrapper around the current result row, so it is only valid
     *          while the row from the Statement remains valid, that is only until next executeStep() call.
     *          Thus, you should instead extract immediately its data (getInt(), getText()...)
     *          and use or copy this data for any later usage.
     */
    Column  getColumn(const int index); // throw(SQLite::Exception);

    /**
     * @brief Return a copie of the column data specified by its index
     *
     *  Can be used to access the data of the current row of result when applicable,
     * while the executeStep() method returns true.
     *
     *  Throw an exception if there is no row to return a Column from :
     * - before any executeStep() call
     * - after the last executeStep() returned false
     * - after a reset() call
     *
     *  Throw an exception if the specified index is out of the [0, getColumnCount()) range.
     *
     * @param[in] index    Index of the column, starting at 0
     * @param[out] column  the Column point.use must delete after call
     *
     * @note    This method is no more const, starting in v0.5,
     *          which reflects the fact that the returned Column object will
     *          share the ownership of the underlying sqlite3_stmt.
     *
     * @warning The resulting Column object must not be memorized "as-is".
     *          Is is only a wrapper around the current result row, so it is only valid
     *          while the row from the Statement remains valid, that is only until next executeStep() call.
     *          Thus, you should instead extract immediately its data (getInt(), getText()...)
     *          and use or copy this data for any later usage.
     */
    void getColumn(const int index,Column** column);
    /**
     * @brief Test if the column value is NULL
     *
     * @param[in] index    Index of the column, starting at 0
     *
     * @return true if the column value is NULL
     */
    bool    isColumnNull(const int index) const; // throw(SQLite::Exception);

    ////////////////////////////////////////////////////////////////////////////

    /// @brief Return the UTF-8 SQL Query.
    inline const std::string& getQuery(void) const
    {
        return _query;
    }
    /// @brief Return the number of columns in the result set returned by the prepared statement
    inline int getColumnCount(void) const
    {
        return _columnCount;
    }
    /// @brief true when a row has been fetched with executeStep()
    inline bool isOk(void) const
    {
        return _ok;
    }
    /// @brief true when the last executeStep() had no more row to fetch
    inline bool isDone(void) const
    {
        return _done;
    }
    /// @brief Return UTF-8 encoded English language explanation of the most recent error.
    inline const char* errmsg(void) const
    {
        return sqlite3_errmsg(_stmtPtr);
    }

public:
    /**
     * @brief Shared pointer to the sqlite3_stmt SQLite Statement Object.
     *
     * Manage the finalization of the sqlite3_stmt with a reference counter.
     *
     * This is a internal class, not part of the API (hence full documentation is in the cpp).
     */
    class Ptr
    {
    public:
        // Prepare the statement and initialize its reference counter
        Ptr(sqlite3* apSQLite, std::string& aQuery);
        // Copy constructor increments the ref counter
        Ptr(const Ptr& aPtr);
        // Decrement the ref counter and finalize the sqlite3_stmt when it reaches 0
        ~Ptr(void) throw(); // nothrow (no virtual destructor needed here)

        /// @brief Inline cast operator returning the pointer to SQLite Database Connection Handle
        inline operator sqlite3*() const
        {
            return _db;
        }

        /// @brief Inline cast operator returning the pointer to SQLite Statement Object
        inline operator sqlite3_stmt*() const
        {
            return _stmt;
        }

    private:
        /// @{ Unused/forbidden copy operator
        Ptr& operator=(const Ptr& aPtr);
        /// @}

    private:
        sqlite3*        _db;   //!< Pointer to SQLite Database Connection Handle
        sqlite3_stmt*   _stmt;     //!< Pointer to SQLite Statement Object
        unsigned int*   _refCount; //!< Pointer to the heap allocated reference counter of the sqlite3_stmt (to share it with Column objects)
    };

private:
    /// @{ Statement must be non-copyable
    Statement(const Statement&);
    Statement& operator=(const Statement&);
    /// @}

    /**
     * @brief Check if a return code equals SQLITE_OK, else throw a SQLite::Exception with the SQLite error message
     *
     * @param[in] SQLite return code to test against the SQLITE_OK expected value
     */
    void check(const int aRet) const; // throw(SQLite::Exception);

private:
    std::string     _query;         //!< UTF-8 SQL Query
    Ptr             _stmtPtr;       //!< Shared Pointer to the prepared SQLite Statement Object
    int             _columnCount;   //!< Number of columns in the result of the prepared statement
    bool            _ok;           //!< true when a row has been fetched with executeStep()
    bool            _done;         //!< true when the last executeStep() had no more row to fetch
};

NS_CC_YHGE_SQLITE_END

#endif //YHGE_SQLITE_STATEMENT_H_
