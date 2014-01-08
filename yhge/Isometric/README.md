一.关于原始tiled map说明。
map由layer和object group组成。这二个层的元素都由tile显示(object group还可以显示多边形)，而tile是在tileset定义的。
同一个tileset里的元素大小是一定的，并且是合并在一张大的图片里。
优点：简单，高效
缺点：不能显示动画，对于复杂的应用不够灵活。由于是分层显示，无法处理复杂遮挡关系。

关于cocos2d支持的tmx:为了使渲染的高效，一个layer只使用一个tileset。只读取object group信息，并未显示。没有处理跨层的遮挡问题。

TODO:
	1.使tileset支持不等大的tile,比如texture packer生成的图片。
	2.扩展tile的定义，使其对应游戏里的任意对象(包括动画)。
	3.渲染object group。
	4.处理遮挡问题。
	5.支持大图片显示。

二.目录说明
parser 处理成中间数据。
reader 直接生成最终结果。

三.
类的关系
										TileLayer
										
						GroundTileLayer		BatchTileLayer		DynamicTileLayer	BatchDynamicTileLayer	