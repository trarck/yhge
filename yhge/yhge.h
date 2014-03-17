#ifndef COCOS_YHGE_H_
#define COCOS_YHGE_H_

#include "YHGEMacros.h"

//smart pointer
#include "SmartPointer/smart_ptr.h"

//Arithmetic
#include "Arithmetic/Search/AStar/AstarNode.h"
#include "Arithmetic/Search/AStar/Astar.h"
#include "Arithmetic/Search/AStar/AstarFlexible.h"
#include "Arithmetic/Search/AStar/CallbackAstar.h"

//CocosExt
#include "CocosExt/Actions/CCParabolaMove.h"
#include "CocosExt/CCCallFuncNO.h"
#include "CocosExt/CCGeometryValue.h"
#include "CocosExt/CCSelectorWrap.h"
#include "CocosExt/Support/CCVector.h"
#include "CocosExt/Support/CCMap.h"
#include "CocosExt/Support/CCValue.h"
#include "CocosExt/CCAdaptSprite.h"

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

//sqlite wrap
#include "Sqlite/SqliteMacros.h"
#include "Sqlite/Statement.h"
#include "Sqlite/Column.h"
#include "Sqlite/Transaction.h"
#include "Sqlite/SqliteDB.h"

//data
#include "Datas/BaseData.h"
#include "Datas/JSONData.h"
#include "Datas/CocosData.h"

//FSM
#include "FSM/Common/FSMState.h"
#include "FSM/Common/FSMParameterState.h"
#include "FSM/Common/FSMDelegateState.h"
#include "FSM/Common/FSMMachine.h"

#endif //COCOS_YHGE_H_