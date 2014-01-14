#include "MoveComponent.h"

NS_CC_YHGE_BEGIN

MoveComponent();

~MoveComponent();

void dealloc
{
	self.currentPaths=NULL;
	self.nextPaths=NULL;
	[super dealloc];
}

bool init
{
	if((self=[super init])){
		m_direction.x=0;
		m_direction.y=0;
		m_currentPaths=NULL;
		m_nextPaths=NULL;
		moving_=NO;
		m_moveState=MoveStop;
		m_speed=0.25;
	}
	return self;
}

bool initWithSpeed:(float) speed
{
	if ((self=[self init])) {
		m_speed=speed;
	}
	return self;
}

CCPoint movingCoordinate
{
	CGPoint coord;
	if (m_moveState==MoveStart) {
		coord=m_to;
	}else {
		coord.x=owner_.mx;
		coord.y=owner_.my;
	}
	return coord;
}

#pragma mark -
#pragma mark 移动

/**
 * 按指定路径移动
 */
void moveWithPaths:(NSArray *) paths
{
	[self moveWithPaths:paths fromIndex:0];
}

void moveWithPaths:(NSArray *)paths fromIndex:(int) fromIndex
{
	updateStep_=@selector(updatePath:);
	if (m_moveState==MoveStart) {
		fromIndex_=fromIndex;
		[self continueMoveWithPaths:paths];
	}else if(m_moveState==MoveStop){
		fromIndex_=fromIndex;
		self.currentPaths=paths;
		[self preparePath];
		if ([self beforeMovePath]) {
			[self startMove];
		}
	}
}
/**
 * 继续指定路径移动
 */
void continueMoveWithPaths:(NSArray *) paths
{
	self.nextPaths=paths;	
	m_moveState=MoveContinue;
}

/**
 * 按指定方向类型移动
 */
void moveWithDirectionType:(int) dirType
{
	//	switch (dir) {
	//		case ISO_NORTH:
	//			
	//			break;
	//		default:
	//			break;
	//	}
}

/**
 * 按指定方向移动
 */
void moveWithDirection:(float) dirX dirY:(float)dirY
{
	CGPoint dir={dirX,dirY};
	[self moveWithDirection:dir];
	
}

/**
 * 按指定方向移动
 */
void moveWithDirection:(CGPoint) dir
{
	updateStep_=@selector(updateDirection:);
	
	if (m_moveState==MoveStart) {
		[self continueMoveWithDirection:dir];
	}else {
		[self setDirection:dir];	
		
		if([self beforeMove]){
			//update move action
			[self updateMoveAnimation];
			[self startMove];
		}
	}
}

/**
 * 断续指定方向移动
 */
void continueMoveWithDirection:(CGPoint) dir
{
	nextDirection_=dir;	
	m_moveState=MoveContinue;
}

/**
 * 移动之前进行检查
 */

bool beforeMove
{
	//NSLog(@"beforMove:%f,%f %f,%f:%@",mx,my,m_to.x,m_to.y,[MapData sharedMapData]);
//	MapData *mapData=[MapData sharedMapData];//[map_ getMapData];
//	//检查to_所在的格子是否可以通过
//	unsigned short barrier=[mapData mapInfoBarrierWithCoord:m_to];
//	if (barrier) {
//		if (m_moveState==MoveStart) {
//			//已经开始移动，则停止
//			m_moveState=MoveWillStop;
//			[self stopMove];
//		}
//		//被阻断(发生碰撞)
//		[self didHit:m_to];
//		return NO;
//	}
//	//clear current grid 
//	[mapData removeMapDataWithEntity:self];
//	
//	//set to data
//	int x=(int)m_to.x,y=(int) m_to.y;
//	
//	for ( int i=0; i<l_; i++) {
//		for (int j=0; j<b_; j++) {
//			[mapData setMapInfoWithX:x+j y:y+i entity:self];
//		}
//	}
	return YES;
}

/**
 * 路径移动之前进行检查
 */
bool beforeMovePath
{
	if([self beforeMove]){
		[self calcDirection];
		//update move action
		[self updateMoveAnimation];
		return YES;
	}
	return NO;
}

/**
 * 开始移动
 * 设置移动动画的定时器
 */
void startMove
{
	m_moveState=MoveStart;
	//[self scheduleUpdate];
	//[self schedule:@selector(updatePath:)];
	//[self schedule:updateStep_];
	[[CCScheduler sharedScheduler] scheduleUpdateForTarget:self priority:0 paused:NO];
	
	//NSLog(@"start entity move schedule:update");
}

/**
 * 停止移动
 * 取消移动动画的定时器
 */
void stopMove
{
	if(m_moveState==MoveStart){
		m_moveState=MoveWillStop;
	}else {
		//[self unscheduleUpdate];
		//[self unschedule:@selector(updatePath:)];
		//[self unschedule:updateStep_];
		[[CCScheduler sharedScheduler] unscheduleUpdateForTarget:self];
		m_moveState=MoveStop;
		//NSLog(@"stop entity move schedule:update");
		[self didMoveStop];
	}
}

//void restartMove
//{
//	m_moveState=MoveStart;
//	[self preparePath];
//	[self beforeMovePath];
//}

/**
 * 移动动画步骤
 * 通过方向移动的动画步骤
 */
void updateDirection:(ccTime) delta
{
	float mx=owner_.mx,my=owner_.my;
	//根据速度计算移动距离
    float s=m_speed*delta*10;
	mx+=s*m_direction.x;
	my+=s*m_direction.y;
	//判断是否结束	
	if (( m_direction.x * mx>m_direction.x*m_to.x || fabs(mx-m_to.x)<0.00001) && ( m_direction.y*my> m_direction.y * m_to.y	|| fabs(my-m_to.y)<0.00001)) {
		mx=m_to.x;
		my=m_to.y;
		
		if (m_moveState==MoveContinue) {
			if (nextDirection_.x!=0 && nextDirection_.y!=0) {
				m_moveState=MoveStart;
				[self setDirection:nextDirection_];
				if([self beforeMove]){
					//update move action
					[self updateMoveAnimation];
				}
			}
		}else {
			//stop move
			m_moveState=MoveWillStop;//标记将要结束
			[self stopMove];
		}
	}
	[owner_ setCoordinate:mx y:my];
}
/**
 * 移动动画步骤
 * 通过路径移动的动画步骤
 */
void updatePath:(ccTime) delta
{
	float mx=owner_.mx,my=owner_.my;
	//根据速度计算移动距离
    float s=m_speed*delta*10;
	mx+=s*m_direction.x;
	my+=s*m_direction.y;
	
	//判断是否结束	
	if (( m_direction.x * mx>m_direction.x*m_to.x || fabs(mx-m_to.x)<0.00001) && ( m_direction.y*my> m_direction.y * m_to.y	|| fabs(my-m_to.y)<0.00001)) {
		mx=m_to.x;
		my=m_to.y;

		if (m_moveState==MoveContinue) {
			if (m_nextPaths!=NULL) {
				m_moveState=MoveStart;
				self.currentPaths=m_nextPaths;
				[self preparePath];
				[self beforeMovePath];
			}
		}else if (--m_spathIndex>=0 && m_moveState==MoveStart) {
			//进行下一个格子
			m_to=[[m_currentPaths objectAtIndex:m_spathIndex] CGPointValue];
			[self beforeMovePath];
		}else {
			//stop move
			self.currentPaths=NULL;
			m_moveState=MoveWillStop;//标记将要结束
			[self stopMove];
		}
	}
	[owner_ setCoordinate:mx y:my];
}

/**
 * 准备移动路径
 */
void  preparePath
{
	m_spathIndex=[m_currentPaths	count]-2-fromIndex_;
	if (m_spathIndex<0) {
		NSAssert(m_spathIndex<0,@"paths length less 2");
	}
	
	m_to=[[m_currentPaths objectAtIndex:m_spathIndex] CGPointValue];
}

/**
 * 计算方向
 * 主要用于按路径移动时
 */
void calcDirection
{
	lastDirection_=m_direction;
	float mx=owner_.mx,my=owner_.my;
	m_direction.x=m_to.x>mx?1:m_to.x<mx?-1:0;
	m_direction.y=m_to.y>my?1:m_to.y<my?-1:0;
}

/**
 * 设置方向
 * 用于按方向移动
 */
void setDirection:(float) dirX dirY:(float)dirY
{
	lastDirection_=m_direction;
	
	m_direction.x=dirX;
	m_direction.y=dirY;
	
	m_to.x=owner_.mx+dirX;
	m_to.y=owner_.my+dirY;
}

/**
 * 设置方向
 * 用于按方向移动
 */
void setDirection:(CGPoint) dir
{
	lastDirection_=m_direction;
	
	m_direction=dir;
	
	m_to.x=owner_.mx+dir.x;
	m_to.y=owner_.my+dir.y;
}

//void clearMapData
//{
//	MapData *mapData=[MapData sharedMapData];
//	int x,y;
//	if (m_moveState!=MoveStop) {
//		x=(int)m_to.x;
//		y=(int)m_to.y;
//	}else {
//		x=(int)mx;
//		y=(int)my;
//	}
//	
//	for ( int i=0; i<l_; i++) {
//		for (int j=0; j<b_; j++) {
//			[mapData removeMapInfoWithX:x+j y:y+i entity:self];
//		}
//	}
//}
/**
 * 方向改变
 * 人物在移动时要面向不同的方向
 */
void updateMoveAnimation
{
	
}
/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void didMoveStop
{
	
}
//处理碰撞,由子类实现。
//TODO:触发事件。由事件接收者执行处理逻辑，比如重新寻路。、
void didHit:(CGPoint) location
{
	
}

NS_CC_YHGE_END
