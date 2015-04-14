#include "JSONSqliteDAO.h"

USING_NS_CC;

USING_NS_CC_YHGE_SQLITE;

NS_CC_YHGE_DATA_BEGIN

static const char* kSqlSeprate=",";
static const char* kSqlFieldQuto="`";
static const char* kSqlNullValue="null";
static const char* kSqlDefaultPrepareFlag=":";

JSONSqliteDAO::JSONSqliteDAO()
:_driver(NULL)
,_prepareFlag(kSqlDefaultPrepareFlag)
{

}

JSONSqliteDAO::~JSONSqliteDAO()
{
    CC_SAFE_RELEASE_NULL(_driver);
}

bool JSONSqliteDAO::init()
{
    sqlite::SqliteDriver* sqliteDriver=new sqlite::SqliteDriver();
    
    _driver=new CocosSqliteDriver(sqliteDriver);
    
    return true;
}

bool JSONSqliteDAO::init(const std::string& dbPath,int flag)
{
    sqlite::SqliteDriver* sqliteDriver=new sqlite::SqliteDriver();
    
    _driver=new CocosSqliteDriver(sqliteDriver);
    
    sqliteDriver->connect(dbPath,flag);
    
    return true;
}

bool JSONSqliteDAO::init(CocosSqliteDriver* driver)
{
    setDriver(driver);
    
    return true;
}

int JSONSqliteDAO::fetchNumber(const std::string& querySql)
{
    Statement stmt(*(_driver->getPtr()),querySql);
    
    if(stmt.execute()){
    
        Column col=stmt.getColumn(0);
        
        return col.getInt();
    }
    
    return 0;
}

//带参数的查询
int JSONSqliteDAO::fetchNumber(const std::string& querySql,const Json::Value& params)
{
    Statement stmt(*(_driver->getPtr()),querySql);
    
    //bind parameter
    bindParams(stmt, params);
    
    if(stmt.execute()){
        
        Column col=stmt.getColumn(0);
        
        return col.getInt();
    }
    
    return 0;
}

Json::Value JSONSqliteDAO::fetchAll(const std::string& querySql)
{
    Statement stmt(*(_driver->getPtr()), querySql);
    
    int colCount=stmt.getColumnCount();
    
    Json::Value result;
    
    while (stmt.executeStep()) {

        Json::Value record;
        
        for (int i=0; i<colCount; i++) {
            setRecordValue(stmt.getColumn(i),record);
        }
        
        result.append(record);
    }
    
    return result;

}

//带参数的查询
Json::Value JSONSqliteDAO::fetchAll(const std::string& querySql,const Json::Value& params)
{
    Statement stmt(*(_driver->getPtr()), querySql);
    
    //bind parameter
    bindParams(stmt, params);
    
    int colCount=stmt.getColumnCount();
    
    Json::Value result;
    
    while (stmt.executeStep()) {
        
        Json::Value record;
        
        for (int i=0; i<colCount; i++) {
            setRecordValue(stmt.getColumn(i),record);
        }
        
        result.append(record);
    }
    
    return result;
}

Json::Value JSONSqliteDAO::fetchOne(const std::string& querySql)
{
    Statement stmt(*(_driver->getPtr()), querySql);
    
    int colCount=stmt.getColumnCount();
    
    Json::Value result;

    if (stmt.executeStep()) {
        for (int i=0; i<colCount; i++) {
            setRecordValue(stmt.getColumn(i),result);
        }
    }
    
    return result;
}

//带参数的查询
Json::Value JSONSqliteDAO::fetchOne(const std::string& querySql,const Json::Value& params)
{
    Statement stmt(*(_driver->getPtr()), querySql);
    
    //bind parameter
    bindParams(stmt, params);
    
    int colCount=stmt.getColumnCount();
    
    Json::Value result;
    
    if (stmt.executeStep()) {
        for (int i=0; i<colCount; i++) {
            setRecordValue(stmt.getColumn(i),result);
        }
    }
    
    return result;
}

Json::Value JSONSqliteDAO::load(const std::string& querySql)
{
    Statement stmt(*(_driver->getPtr()), querySql);
    
    int colCount=stmt.getColumnCount();
    
    Json::Value result;
    
    if (stmt.executeStep()) {
        for (int i=0; i<colCount; i++) {
            setRecordValue(stmt.getColumn(i),result);
        }
    }
    
    return result;
}

//带参数的查询
Json::Value JSONSqliteDAO::load(const std::string& querySql,int value)
{
    Statement stmt(*(_driver->getPtr()), querySql);
    
    //bind key value
    stmt.bind(1, value);
    
    int colCount=stmt.getColumnCount();
    
    Json::Value result;
    
    if (stmt.executeStep()) {
        for (int i=0; i<colCount; i++) {
            setRecordValue(stmt.getColumn(i),result);
        }
    }
    
    return result;
}

//带参数的查询
Json::Value JSONSqliteDAO::load(const std::string& querySql,const std::string& value)
{
    Statement stmt(*(_driver->getPtr()), querySql);
    
    //bind key value
    stmt.bind(1, value);
    
    int colCount=stmt.getColumnCount();
    
    Json::Value result;
    
    if (stmt.executeStep()) {
        for (int i=0; i<colCount; i++) {
            setRecordValue(stmt.getColumn(i),result);
        }
    }
    
    return result;
}

int JSONSqliteDAO::insert(const std::string& insertSql)
{
    return _driver->getPtr()->execute(insertSql);
}

int JSONSqliteDAO::update(const std::string& updateSql)
{
    return _driver->getPtr()->execute(updateSql);
}

int JSONSqliteDAO::remove(const std::string& deleteSql)
{
    return _driver->getPtr()->execute(deleteSql);
}

int JSONSqliteDAO::insert(const std::string& table,const Json::Value& data)
{
    //生成sql
    std::string insertSql = "INSERT INTO "+table+" ";
    
    insertSql+=formateToInsertPrepare(data);
    
    insertSql+=";";
    
    Statement stmt(*(_driver->getPtr()), insertSql);
    
    //绑定变量
    Json::Value::Members members=data.getMemberNames();
    
    for (Json::Value::Members::iterator iter=members.begin(); iter!=members.end(); ++iter) {
        bindStatement(stmt,*iter,data[*iter]);
    }
    
    return stmt.execute();
}

void JSONSqliteDAO::batchInsert(const std::string& table,const Json::Value& data)
{
    //准备sql
    std::string insertSql = "INSERT INTO "+table+" ";
    
    insertSql+=formateToInsertPrepare(data[0u]);
    
    insertSql+=";";
    
    //只使用一个statement
    Statement stmt(*(_driver->getPtr()), insertSql);
    
    
    int count=data.size();
    
    for(unsigned int i=0;i<count;++i){
        
        //如果不是第一个使用stmt，要重置下。
        if (i!=0) {
            stmt.reset();
        }
        
        //分别绑定每一条记录
        Json::Value record=data[i];
        
        Json::Value::Members members=record.getMemberNames();
        
        for (Json::Value::Members::iterator iter=members.begin(); iter!=members.end(); ++iter) {
            bindStatement(stmt,*iter,record[*iter]);
        }
        stmt.execute();
    }
}

int JSONSqliteDAO::update(const std::string& table,const Json::Value& data,const Json::Value& where)
{
    //生成sql
    std::string updateSql = "UPDATE "+table+" SET ";
    
    updateSql+=formateToEqualPrepare(data);
    
    //检查有没有更新条件
    if (where.isNull()) {
        
        updateSql+=";";
        
        Statement stmt(*(_driver->getPtr()), updateSql);
        
        //绑定更新数据
        Json::Value::Members members=data.getMemberNames();
        
        for (Json::Value::Members::iterator iter=members.begin(); iter!=members.end(); ++iter) {
            bindStatement(stmt,*iter,data[*iter]);
        }
        
        return stmt.execute();
        
    }else{
        //生成where语句
        Json::Value whereData;
        
        std::string whereSql=formateToConditionPrepare(where, whereData);
        
        updateSql+=" WHERE "+whereSql;
        
        updateSql+=";";
        
        Statement stmt(*(_driver->getPtr()), updateSql);
        
        //由于带标志符的也占用位置，所以问号表示的不是问号中的位置，而是整个参数中的位置。所以要跳过更新数据的变量。
        int i=1;
        
        //绑定更新数据
        Json::Value::Members members=data.getMemberNames();
   
        for (Json::Value::Members::iterator iter=members.begin(); iter!=members.end(); ++iter) {
            bindStatement(stmt,*iter,data[*iter]);
            ++i;
        }
        
        //绑定where数据
        int size=whereData.size();
        
        for (int j=0;j<size;++j) {
            bindStatement(stmt,i++,whereData[j]);
        }
        
        return stmt.execute();
    }
}

int JSONSqliteDAO::remove(const std::string& table,const Json::Value& where)
{
    //生成sql
    std::string deleteSql = "DELETE FROM "+table+" WHERE ";
    
    Json::Value whereData;
    
    deleteSql+=formateToConditionPrepare(where,whereData);
    
    deleteSql+=";";
    
    Statement stmt(*(_driver->getPtr()), deleteSql);
    
    //绑定条件数据
    int size =whereData.size();
    for (int i=0; i<size; ++i){
        bindStatement(stmt,i+1,whereData[i]);
    }
    
    return stmt.execute();
}

/*
 
 {
 
    "a":1,
    "b":2,
    "c":3
 }
 
 =>
 
 (`a`,`b`,`c`) values (:a,:b,:c)
 
 
 */
std::string JSONSqliteDAO::formateToInsertPrepare(const Json::Value& data)
{
    
    std::string fields="(";
    std::string values="(";
    
    bool isFirst=true;
    
    Json::Value::Members members=data.getMemberNames();
    for (Json::Value::Members::iterator iter=members.begin(); iter!=members.end(); ++iter) {
        
        //如果不是第一项，则加入分割符
        if (isFirst) {
            isFirst=false;
        }else{
            fields+=kSqlSeprate;
            values+=kSqlSeprate;
        }
        //`a`
        fields+= kSqlFieldQuto+ *iter + kSqlFieldQuto;
        
        //:a
        values+= _prepareFlag + *iter;
    }
    
    fields+=")";
    values+=")";
    
    return fields + " values " + values;
}

/*
 
 {
 
 "a":1,
 "b":2,
 "c":3
 }
 
 =>
 
 `a`=:a,`b`=:b,`c`=:c
 
 */
std::string JSONSqliteDAO::formateToEqualPrepare(const Json::Value& data)
{
    
    std::string prepareStr="";
    
    bool isFirst=true;
    
    Json::Value::Members members=data.getMemberNames();
    
    for (Json::Value::Members::iterator iter=members.begin(); iter!=members.end(); ++iter) {
        
        //如果不是第一项，则加入分割符
        if (isFirst) {
            isFirst=false;
        }else{
            prepareStr+=kSqlSeprate;
        }
        
        //`a`=:a
        prepareStr+= kSqlFieldQuto+ *iter + kSqlFieldQuto
                    + "="
                    + _prepareFlag + *iter;
    }
    
    return prepareStr;
}

/*
 由于条件可以嵌套，并且可能会有重复，所以使用?来绑定
 {
 
 "a":1,
 "b":2,
 "c":3
 }
 
 =>
 
 `a`=? AND `b`=? AND `c`=?
 
 {
 
 "a":1,
 
 "OR":{
     "b":2,
     "c":3
  }
 }
 
 `a`=? AND (`b`=? OR `c`=?)
 
 */
std::string JSONSqliteDAO::formateToConditionPrepare(const Json::Value& data,Json::Value& whereData,const std::string& separator)
{

    std::string prepareStr="";
    
    bool isFirst=true;
    
    Json::Value::Members members=data.getMemberNames();
    
    for (Json::Value::Members::iterator iter=members.begin(); iter!=members.end(); ++iter) {
        
        if (isFirst) {
            isFirst=false;
        }else{
            prepareStr+=" "+separator+" ";
        }
        
        if (*iter=="AND" || *iter=="OR") {
            
            prepareStr+= "("+formateToConditionPrepare(data[*iter],whereData,*iter)+")";
            
        }else{
            whereData.append(data[*iter]);
            
            //`a`=?
            prepareStr+= kSqlFieldQuto+ *iter + kSqlFieldQuto + "= ?";
        }
    }
    
    return prepareStr;
}

void JSONSqliteDAO::setRecordValue(const sqlite::Column& col, Json::Value& record)
{
    switch (col.getType()) {
        case SQLITE_INTEGER:
            record[col.getName()]=col.getInt();
            break;
        case SQLITE_FLOAT:
            record[col.getName()]=col.getDouble();
            break;
        case SQLITE_BLOB:{
            char* blobBegin=(char*)col.getBlob();
            char* blobEnd=blobBegin+col.getBytes();
            record[col.getName()]=Json::Value(blobBegin,blobEnd);
            break;
        }
        case SQLITE_NULL:
            record[col.getName()]=Json::Value::null;
            break;
        case SQLITE_TEXT:
            record[col.getName()]=col.getText();
            break;
        default:
            break;
    }
}

void JSONSqliteDAO::bindParams(sqlite::Statement& stmt,const Json::Value& params)
{
    Json::ValueType type=params.type();
    if(type==Json::arrayValue){
        
        int size=params.size();
        
        for (int i=0; i<size; ++i) {
            bindStatement(stmt,i+1,params[i]);
        }
        
    }else if (type==Json::objectValue){
        
        Json::Value::Members members=params.getMemberNames();
        
        for (Json::Value::Members::iterator iter=members.begin(); iter!=members.end(); ++iter) {
            bindStatement(stmt,*iter,params[*iter]);
        }
    }
}

void JSONSqliteDAO::bindStatement(Statement& stmt,const std::string& name,const Json::Value& val)
{
    switch (val.type()) {
        case Json::intValue:
            stmt.bind(_prepareFlag+name, val.asInt());
            break;
        case Json::realValue:
            stmt.bind(_prepareFlag+name, val.asDouble());
            break;
        case Json::stringValue:
            stmt.bind(_prepareFlag+name, val.asString());
            break;
        case Json::booleanValue:
            stmt.bind(_prepareFlag+name, val.asBool()?1:0);
            break;
        case Json::nullValue:
            stmt.bind(_prepareFlag+name,kSqlNullValue);
            break;
        default:
            break;
    }
}

void JSONSqliteDAO::bindStatement(Statement& stmt,int index,const Json::Value& val)
{
    switch (val.type()) {
        case Json::intValue:
            stmt.bind(index, val.asInt());
            break;
        case Json::realValue:
            stmt.bind(index, val.asDouble());
            break;
        case Json::stringValue:
            stmt.bind(index, val.asString());
            break;
        case Json::booleanValue:
            stmt.bind(index, val.asBool()?1:0);
            break;
        case Json::nullValue:
            stmt.bind(index,kSqlNullValue);
            break;
        default:
            break;
    }
}



NS_CC_YHGE_DATA_END
