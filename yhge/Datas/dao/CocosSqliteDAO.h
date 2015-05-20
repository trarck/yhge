#ifndef YHGE_DATA_DAO_COCOSSQLITEDAO_H_
#define YHGE_DATA_DAO_COCOSSQLITEDAO_H_

#include "cocos2d.h"
#include <yhge/Sqlite/SqliteDriver.h>
#include <yhge/CocosExt/CCRef.h>
#include <yhge/CocosExt/CCSimpleValue.h>
#include "DAO.h"

NS_CC_YHGE_DATA_BEGIN

typedef CCRef<sqlite::SqliteDriver> CocosSqliteDriver;

class CocosSqliteDAO:public DAO
{
public:
    
	CocosSqliteDAO();
    
	~CocosSqliteDAO();
    
    bool init();
    
    bool init(const std::string& dbPath,int flag);
    
    bool init(CocosSqliteDriver* driver);
    
    /**
     * @brief 取得第一行第一列的值。为了方便count(*)
     *
     * @return int 值
     */
    int fetchNumber(const std::string& querySql);
    
    /**
     * @brief 取得所有查询结果
     *
     * @return json的数组
     */
    ValueVector fetchAll(const std::string& querySql);
    
    /**
     * @brief 取得第一条查询结果
     *
     * @return json的对象
     */
    ValueMap fetchOne(const std::string& querySql);
    
    /**
     * @brief 执行sql语句
     * 通常不用取得反回值。像insert,update,delete等。
     *
     * @return 影响的行数
     */
    int execute(const std::string sql);
    
    /**
     * @brief 执行插入语句
     *
     * @return 影响的行数
     */
    int insert(const std::string& insertSql);
    
    /**
     * @brief 执行更新语句
     *
     * @return 影响的行数
     */
    int update(const std::string& updateSql);
    
    /**
     * @brief 执行删除语句
     *
     * @return 影响的行数
     */
    int remove(const std::string& deleteSql);
    
    /**
     * @brief 像一个表里插入数据
     *
     * @return 影响的行数
     */
    int insert(const std::string& table,const ValueMap& data);
    
    /**
     * @brief 批量像一个表里插入数据
     * 每条数据的列相同
     *
     * @return 影响的行数
     */
    void batchInsert(const std::string& table,const ValueVector& data);
    
    /**
     * @brief 更新一个表里数据
     *
     * @return 影响的行数
     */
	int update(const std::string& table, const ValueMap& data, const ValueMap& where);
    
    /**
     * @brief 删除一个表里数据
     *
     * @return 影响的行数
     */
	int remove(const std::string& table, const ValueMap& where);
    
    
    /**
     * @brief 格式化数据成插入方便使用的语句
     *
     * @return insert的values
     */
	std::string formateToInsertPrepare(const ValueMap& data);
    
    /**
     * @brief 格式化数据成赋值方便使用的语句
     *
     * @return update的set
     */
	std::string formateToEqualPrepare(const ValueMap& data);
    
    
    /**
     * @brief 格式化数据成条件方便使用的语句
     *
     * @return where的条件
     */
	std::string formateToConditionPrepare(const ValueMap& data, ValueVector& whereData, const std::string& separator = "AND");
    
protected:
    
    /**
     * @brief 设置一个记录的列值
     */
	void setRecordValue(const sqlite::Column& col, ValueMap& record);
    
//    /**
//     * @brief 绑定一个列值
//     */
//    void bindStatement(sqlite::Statement& stmt,const std::string& name,Ref* val);
//    
//    /**
//     * @brief 绑定一个列值
//     */
//    void bindStatement(sqlite::Statement& stmt,int index,Ref* val);
    
    /**
     * @brief 绑定一个列值
     */
    void bindStatement(sqlite::Statement& stmt,const std::string& name,const Value& val);
    
    /**
     * @brief 绑定一个列值
     */
    void bindStatement(sqlite::Statement& stmt,int index,const Value& val);
    
public:
    
    inline CocosSqliteDriver* getDriver()
    {
        return _driver;
    }
    
    inline void setDriver(CocosSqliteDriver* driver)
    {
        CC_SAFE_RETAIN(driver);
        CC_SAFE_RELEASE(_driver);
        _driver = driver;
    }
    
    inline void setPrepareFlag(const std::string& prepareFlag)
    {
        _prepareFlag = prepareFlag;
    }
    
    inline const std::string& getPrepareFlag()
    {
        return _prepareFlag;
    }
    
protected:
    
    CocosSqliteDriver* _driver;
    
    std::string _prepareFlag;  
    

};

NS_CC_YHGE_DATA_END



#endif //YHGE_DATA_DAO_COCOSSQLITEDAO_H_
