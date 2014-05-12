一、组件系统的三种模式
1、fat entity+component
	entity保存通用的属性,component没有属性只有逻辑。
	由于entity保持了属性，导致灵活性降低，不适合大型项目。
2、thin entity+component
    entity只有id,没有其它属性，属性都在component。
	由于entity没有东西，灵活性强，component有属性，之间的引用关系就也增加，如果只是单存的通过消息来传递component之前的通信,性能会有所降低。
	通常把需要的component作为属性添加到component中，但这样就增加了component之前的耦合。
3、entity system
    entity只有id,component只有属性没有逻辑，逻辑都在entity里。可以看成是一和二的结合体。
	如果把entity的属性拿出来叫property,component只有逻辑就是现在这个版本。为了和国际接轨则把property叫作component,把component叫作system，就是entity system系统。
	
二、组件的更新方法
  1.在entity里更新
  	component定义一个update的接口，entity也定义一个update接口，在entity manager里调用entity的update,再在entity的update里调用component的update。
	由于实现简单，适用中小型的逻辑
  2.由component自己定义
    外部实现一个定时器，component把自己注册到该管理器，由管理器调用component的update.
	中间逻辑比较复杂，适用中大型项目。