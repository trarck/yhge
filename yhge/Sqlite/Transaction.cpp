/**
 * @file    Transaction.cpp
 * @ingroup SQLiteCpp
 * @brief   A Transaction is way to group multiple SQL statements into an atomic secured operation.
 *
 * Copyright (c) 2012-2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#include "Transaction.h"

#include "SqliteDriver.h"

NS_CC_YHGE_SQLITE_BEGIN

// Begins the SQLite transaction
Transaction::Transaction(SqliteDriver& driver) : // throw(SQLite::Exception)
    m_driver(driver),
    m_commited(false)
{
    m_driver.execute("BEGIN");
}

// Safely rollback the transaction if it has not been committed.
Transaction::~Transaction(void) throw() // nothrow
{
    if (false == m_commited)
    {
        m_driver.execute("ROLLBACK");
    }
}

// Commit the transaction.
void Transaction::commit(void) // throw(SQLite::Exception)
{
    if (false == m_commited)
    {
        m_driver.execute("COMMIT");
        m_commited = true;
    }
    else
    {
        CCLOGERROR("Transaction already commited");
    }
}

NS_CC_YHGE_SQLITE_END
