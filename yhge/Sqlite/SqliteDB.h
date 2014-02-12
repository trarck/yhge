#ifndef YHGE_SQLITE_SQLITEDB_H_
#define YHGE_SQLITE_SQLITEDB_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <sqlite3.h>
#include "SqliteMacros.h"
#include "Column.h"

NS_CC_YHGE_SQLITE_BEGIN

class SqliteDB : public CCObject
{
public:
    
    SqliteDB();
    ~SqliteDB();
    
    bool init();
    
    /**
     * @brief Open the provided database UTF-8 filename.
     *
     * Uses sqlite3_open_v2() with readonly default flag, which is the opposite behavior
     * of the old sqlite3_open() function (READWRITE+CREATE).
     * This makes sense if you want to use it on a readonly filesystem
     * or to prevent creation of a void file when a required file is missing.
     *
     * Exception is thrown in case of error, then the Database object is NOT constructed.
     *
     * @param[in] dbPath     UTF-8 path/uri to the database file ("filename" sqlite3 parameter)
     * @param[in] flag        SQLITE_OPEN_READONLY/SQLITE_OPEN_READWRITE/SQLITE_OPEN_CREATE...
     */
    void connect(const std::string& dbPath,const int flag = SQLITE_OPEN_READONLY);
    
    
    /**
     * @brief close database connet
     */
    void close();


    /**
     * @brief Shortcut to execute one or multiple statements without results.
     *
     *  This is useful for any kind of statements other than the Data Query Language (DQL) "SELECT" :
     *  - Data Definition Language (DDL) statements "CREATE", "ALTER" and "DROP"
     *  - Data Manipulation Language (DML) statements "INSERT", "UPDATE" and "DELETE"
     *  - Data Control Language (DCL) statements "GRANT", "REVOKE", "COMMIT" and "ROLLBACK"
     *
     * @see Statement::exec() to handle precompiled statements (for better performances) without results
     * @see Statement::executeStep() to handle "SELECT" queries with results
     *
     * @param[in] query  one or multiple UTF-8 encoded, semicolon-separate SQL statements
     *
     * @return number of rows modified by those SQL statements (INSERT, UPDATE or DELETE)
     *
     * @throw SQLite::Exception in case of error
     */
    int execute(const char* query);
    
    inline int execute(const std::string& query)
    {
        return execute(query.c_str());
    }
    
    /**
     * @brief Shortcut to execute a one step query and fetch the first column of the result.
     *
     *  This is a shortcut to execute a simple statement with a single result.
     * This should be used only for non reusable queries (else you should use a Statement with bind()).
     * This should be used only for queries with expected results (else an exception is fired).
     *
     * @warning WARNING: Be very careful with this dangerous method: you have to
     *          make a COPY OF THE result, else it will be destroy before the next line
     *          (when the underlying temporary Statement and Column objects are destroyed)
     *
     * @see also Statement class for handling queries with multiple results
     *
     * @param[in] sqlStr  an UTF-8 encoded SQL query
     *
     * @return a temporary Column object with the first column of result.
     *
     * @throw SQLite::Exception in case of error
     */
    Column fetchFirstColumn(const char* sqlStr); // throw(SQLite::Exception);
    
    inline Column fetchFirstColumn(const std::string& sqlStr) // throw(SQLite::Exception);
    {
        return fetchFirstColumn(sqlStr.c_str());
    }
    
    /**
     * @brief Shortcut to test if a table exists.
     *
     *  Table names are case sensitive.
     *
     * @param[in] tableName an UTF-8 encoded case sensitive Table name
     *
     * @return true if the table exists.
     *
     * @throw SQLite::Exception in case of error
     */
    bool tableExists(const std::string& tableName);
    
    /**
     * @brief Set a busy handler that sleeps for a specified amount of time when a table is locked.
     *
     * @param[in] timeoutMs    Amount of milliseconds to wait before returning SQLITE_BUSY
     */
    inline int setBusyTimeout(int timeoutMs) // throw(); nothrow
    {
        return sqlite3_busy_timeout(m_db, timeoutMs);
    }
    
    /**
     * @brief Get the rowid of the most recent successful INSERT into the database from the current connection.
     *
     * @return Rowid of the most recent successful INSERT into the database, or 0 if there was none.
     */
    inline sqlite3_int64 getLastInsertRowId(void) const // throw(); nothrow
    {
        return sqlite3_last_insert_rowid(m_db);
    }
    
    /**
     * @brief Return UTF-8 encoded English language explanation of the most recent error.
     */
    inline const char* errmsg(void) const
    {
        return sqlite3_errmsg(m_db);
    }
    
    /**
     * @brief Create or redefine a SQL function or aggregate in the sqlite database.
     *
     *  This is the equivalent of the sqlite3_create_function_v2 command.
     * @see http://www.sqlite.org/c3ref/create_function.html
     *
     * @note UTF-8 text encoding assumed.
     *
     * @param[in] funcName     Name of the SQL function to be created or redefined
     * @param[in] arg        Number of arguments in the function
     * @param[in] eterministic Optimize for deterministic functions (most are). A random number generator is not.
     * @param[in] app         Arbitrary pointer ot user data, accessible with sqlite3_user_data().
     * @param[in] func        Pointer to a C-function to implement a scalar SQL function (apStep & apFinal NULL)
     * @param[in] step        Pointer to a C-function to implement an aggregate SQL function (apFunc NULL)
     * @param[in] final       Pointer to a C-function to implement an aggregate SQL function (apFunc NULL)
     * @param[in] destroy     If not NULL, then it is the destructor for the application data pointer.
     *
     * @throw SQLite::Exception in case of error
     */
    void createFunction(const char*   funcName,
                               int                  arg,
                               bool                 deterministic,
                               void*                app,
                               void               (*func)(sqlite3_context *, int, sqlite3_value **),
                               void               (*step)(sqlite3_context *, int, sqlite3_value **),
                               void               (*final)(sqlite3_context *),
                               void               (*destroy)(void *));
    
    inline void createFunction(const std::string&   funcName,
                               int                  arg,
                               bool                 deterministic,
                               void*                app,
                               void               (*func)(sqlite3_context *, int, sqlite3_value **),
                               void               (*step)(sqlite3_context *, int, sqlite3_value **),
                               void               (*final)(sqlite3_context *),
                               void               (*destroy)(void *))
    {
        createFunction(funcName.c_str(),arg,deterministic,app,func,step,final,destroy);
    }
    
    
    /**
     * @brief Return the filename used to open the database
     */
    inline const std::string& getDBPath()
    {
        return m_dbPath;
    }
    
    inline sqlite3* getDB()
    {
        return m_db;
    }
    
private:
    /// @{ Database must be non-copyable
    SqliteDB(const SqliteDB&);
    SqliteDB& operator=(const SqliteDB&);
    /// @}
    
    /**
     * @brief Check if aRet equal SQLITE_OK, else throw a SQLite::Exception with the SQLite error message
     */
    void check(const int ret) const; // throw(SQLite::Exception);
    
private:
    
    //数据库指针
    sqlite3* m_db;
    
    //数据库路径
    std::string m_dbPath;
};

NS_CC_YHGE_SQLITE_END

#endif // YHGE_SQLITE_SQLITEDB_H_