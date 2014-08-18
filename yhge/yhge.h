#ifndef COCOS_YHGE_H_
#define COCOS_YHGE_H_

#include "YHGEMacros.h"

#include "Base/Log.h"

//smart pointer
#include "SmartPointer/smart_ptr.h"

//Arithmetic
#include "Arithmetic/Search/AStar/AstarNode.h"
#include "Arithmetic/Search/AStar/Astar.h"
#include "Arithmetic/Search/AStar/AstarFlexible.h"
#include "Arithmetic/Search/AStar/CallbackAstar.h"

//DataStructure
#include "DataStructure/LinkedList.h"

//CocosExt
#include "CocosExt/Actions/CCParabolaMove.h"
#include "CocosExt/CCCallFuncNO.h"
#include "CocosExt/CCGeometryValue.h"
#include "CocosExt/CCSelectorWrap.h"
#include "CocosExt/Support/Vector.h"
#include "CocosExt/Support/Map.h"
#include "CocosExt/Support/List.h"
#include "CocosExt/Support/Value.h"
#include "CocosExt/CCAdaptSprite.h"
#include "CocosExt/CCDefaultTexture.h"
#include "CocosExt/CocosValue.h"
#include "CocosExt/CCSimpleValue.h"

//message
#include "message.h"

//event
#include "Event/Event.h"
#include "Event/UIEvent.h"
#include "Event/EventHandle.h"
#include "Event/EventHandleWrap.h"
#include "Event/EventListenerManager.h"
#include "Event/StringifyEventListenerManager.h"

//math
#include "Math/MersenneTwister.h"
#include "Math/RandomMT.h"
#include "Math/FloatUtil.h"

//isometric
#include "isometric.h"

//dimetric
#include "Dimetric/DimetricMacros.h"
#include "Dimetric/StaticSideViewCoordinateFormulae.h"
#include "Dimetric/StaticTopViewCoordinateFormulae.h"

//components
#include "entity_component.h"

//json
#include "Jsoncpp/json.h"

//io
#include "IO/IOMacros.h"
#include "IO/Buffer.h"
#include "IO/InputStream.h"
#include "IO/OutputStream.h"

//sqlite wrap
#include "Sqlite/SqliteMacros.h"
#include "Sqlite/Statement.h"
#include "Sqlite/Column.h"
#include "Sqlite/Transaction.h"
#include "Sqlite/SqliteDriver.h"

//data
#include "Datas/DataMacros.h"
#include "Datas/dao/DAO.h"
#include "Datas/dao/CocosDataDAO.h"
#include "Datas/dao/CocosSqliteDAO.h"
#include "Datas/dao/JSONDataDAO.h"
#include "Datas/dao/JSONSqliteDAO.h"
#include "Datas/dao/DAOFactory.h"

//FSM
#include "FSM/Common/FSMState.h"
#include "FSM/Common/FSMParameterState.h"
#include "FSM/Common/FSMDelegateState.h"
#include "FSM/Common/FSMMachine.h"

//animation
#include "Animation/Resource.h"
#include "Animation/Character.h"
#include "Animation/DisplayProperty.h"
#include "Animation/Frame.h"
#include "Animation/Animation.h"
#include "Animation/AnimationGroup.h"
#include "Animation/AnimationManager.h"
#include "Animation/AnimationSprite.h"
#include "Animation/AvatarFrame.h"
#include "Animation/AvatarSprite.h"

#endif //COCOS_YHGE_H_