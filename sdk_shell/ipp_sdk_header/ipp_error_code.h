#ifndef _IPP_ERROR_CODE_H_
#define _IPP_ERROR_CODE_H_

#define IPP_ERROR_CODE_SUCCESS                                                  0     // 成功

#define IPP_ERROR_CODE_COMMON_PROBUF_PROBUF_IS_NULL                             -1    // IPP Protocol Buffer为空
#define IPP_ERROR_CODE_COMMON_PROBUF_BUF_IS_NULL                                -2    // Buffer为空
#define IPP_ERROR_CODE_COMMON_PROBUF_BUF_NOT_ENOUGH                             -3    // IPP Protocol Buffer空间不够
#define IPP_ERROR_CODE_COMMON_TIMER_SET_SELECT_ERROR                            -4    // 定时器SELECT设置错误
#define IPP_ERROR_CODE_COMMON_CREATE_TIMER_THREAD_ERROR                         -5    // 创建定时器线程错误
#define IPP_ERROR_CODE_COMMON_TIMER_IS_NOT_OVER                                 -6    // 定时器未结束
#define IPP_ERROR_CODE_COMMON_CREATE_TIMER_PIPE_ERROR                           -7    // 创建定时器管道错误
#define IPP_ERROR_CODE_COMMON_PROBUF_ASCII_STR_IS_NULL                          -8    // buf串为空
#define IPP_ERROR_CODE_COMMON_PROBUF_ASCII_STR_SIZE_ERROR                       -9    // buf串长度错误
#define IPP_ERROR_CODE_COMMON_ALLOC_FILED										-10   // 分配内存失败

#define IPP_ERROR_CODE_BUSINESS_LAYER_PROFILE_CONFIG_IS_FULL                    -1101 // IPP profile配置为空
#define IPP_ERROR_CODE_BUSINESS_LAYER_EVENT_DISPATCHER_IS_FULL                  -1102 // 事件分配器为空
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_REQUEST_DISPATCHER_IS_FULL        -1103 // 服务请求分配器为空
#define IPP_ERROR_CODE_BUSINESS_LAYER_DISPATCHE_SERVICE_REQUEST_ERROR           -1104 // 服务请求分配错误
#define IPP_ERROR_CODE_BUSINESS_LAYER_DISPATCHE_EVENT_HANDLER_NULL              -1105 // 事件分配处理器为空
#define IPP_ERROR_CODE_BUSINESS_LAYER_DISPATCHE_SERVICE_REQUEST_HANDLER_NULL    -1106 // 服务请求分配处理器为空
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_REQUEST_HANDLER_SET_NULL          -1107 // 服务请求处理器集为空
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_REQUEST_HANDLER_NULL              -1108 // 服务请求处理器为空
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_GET_OBJ_CLASS_ERROR           -1109 // JNI获取对象类型出错
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_GET_GJVM_ERROR                -1110 // JNI获取虚拟机出错
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_SET_GOBJ_ERROR                -1111 // JNI设置全局对象出错
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_SET_GCLS_ERROR                -1112 // JNI设置全局类出错
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_ATTACH_THREAD_ERROR           -1113 // JNI关联线程
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_DETACH_THREAD_ERROR           -1114 // JNI取消关联线程
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_GET_METHOD_ID_ERROR           -1115 // JNI获取方法ID
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_CALL_METHOD_EXP               -1116 // JNI调用方法出现异常
#define IPP_ERROR_CODE_BUSINESS_LAYER_DEVICE_IMPL_HADLE_SERVICE_REQ_NULL        -1117 // device imple service request null

#define IPP_ERROR_CODE_DEVICE_LAYER_NEW_DEVICE_EVENT_RECIEVE_QUEUE              -2101 // 创建接收队列出错
#define IPP_ERROR_CODE_DEVICE_LAYER_CREATE_HANDLE_DEVICE_EVENT_THREAD           -2102 // 创建接收线程出错
#define IPP_ERROR_CODE_DEVICE_LAYER_RECIEVE_DEVICE_EVENT_NULL                   -2103 // 接收设备事件为空
#define IPP_ERROR_CODE_DEVICE_LAYER_RECIEVE_DEVICE_QUEUE_IS_FULL                -2104 // 接收设备事件队列满
#define IPP_ERROR_CODE_DEVICE_LAYER_RECIEVE_DEVICE_CONFIG_IS_FULL               -2105 // IPP事件接收配置为空
#define IPP_ERROR_CODE_DEVICE_LAYER_CALL_SERVICE_LINK_INFO_NULL                 -2106 // 访问服务，连接信息空
#define IPP_ERROR_CODE_DEVICE_LAYER_LINK_LAYER_CONFIG_NULL                      -2107 // 连接层配置为空
#define IPP_ERROR_CODE_DEVICE_LAYER_CALL_SERVICE_NO_CONFIG                      -2108 // 无调用服务配置
#define IPP_ERROR_CODE_DEVICE_LAYER_CALL_SERVICE_ID_ERROR                       -2109 // 调用服务ID错误
#define IPP_ERROR_CODE_DEVICE_LAYER_CALL_SERVICE_LINK_TYPE_ERR                  -2110 // 访问服务，信息类型不匹配
#define IPP_ERROR_CODE_DEVICE_LAYER_NEW_DEVICE_EVENT_SEND_QUEUE                 -2111 // 创建发送队列出错
#define IPP_ERROR_CODE_DEVICE_LAYER_CREATE_SEND_DEVICE_EVENT_THREAD             -2112 // 创建先送线程出错
#define IPP_ERROR_CODE_DEVICE_LAYER_SEND_DEVICE_EVENT_NULL                      -2113 // 发送设备事件为空
#define IPP_ERROR_CODE_DEVICE_LAYER_SEND_DEVICE_QUEUE_IS_FULL                   -2114 // 发送设备事件队列满
#define IPP_ERROR_CODE_DEVICE_LAYER_SEND_EVENT_LINK_INFO_NULL                   -2115 // 发送事件，连接信息空
#define IPP_ERROR_CODE_DEVICE_LAYER_SEND_EVENT_LINK_TYPE_ERR                    -2116 // 发送事件，信息类型不匹配
#define IPP_ERROR_CODE_DEVICE_LAYER_NEW_DEVICE_SERVICE_REQUEST_QUEUE            -2117 // 创建服务请求队列出错
#define IPP_ERROR_CODE_DEVICE_LAYER_CREATE_HANDLE_DEVICE_SERVICE_REQUEST_THREAD -2118 // 创建服务请求线程出错
#define IPP_ERROR_CODE_DEVICE_LAYER_BE_CALLED_DEVICE_SERVICE_NULL               -2119 // 设备服务被调用为空
#define IPP_ERROR_CODE_DEVICE_LAYER_DEVICE_SERVICE_REQUEST_QUEUE_IS_FULL        -2120 // 接收设备服务请求队列满
#define IPP_ERROR_CODE_DEVICE_LAYER_SEND_SERVICE_RESPONSE_NO_CONFIG             -2121 // 无调用发送调用反馈配置
#define IPP_ERROR_CODE_DEVICE_LAYER_CALL_SERVICE_TIMEOUT                        -2122 // 调用服务超时
#define IPP_ERROR_CODE_DEVICE_LAYER_CHECK_SERVICE_RESPONSE_NOT_MATCH            -2123 // 检查服务反馈不匹配
#define IPP_ERROR_CODE_DEVICE_LAYER_CERTIFICATE_CONTROL_IN_LIST_NULL            -2124 // 认证控制端，在列表中为空
#define IPP_ERROR_CODE_DEVICE_LAYER_SERVICE_REQUEST_CONFIG_IS_FULL              -2125 // IPP服务请求配置为空
#define IPP_ERROR_CODE_DEVICE_LAYER_INIT_SEM_ERROR                              -2126 // 初始化信号量错误
#define IPP_ERROR_CODE_DEVICE_LAYER_CONTROL_IS_NOT_CERTIFICATED                 -2127 // 控制端未认证

#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_LINK_SPECIFIC_NULL                      -3101 // 本地连接连接信息空
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_PROTOCOL_BUFFER_NULL                    -3102 // 本地连接protocol buffer空
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SOCKET_ERROR                            -3103 // 本地连接sock错误
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SENDTO_ERROR                            -3104 // 本地连接sendto错误
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_MAX_RESEND_TIMES                        -3105 // 本地连接达到重发次数
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_NEW_DATA_RECIEVE_QUEUE                  -3106 // 创建本地接收数据队列出错
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_CREATE_DATA_RECIEVE_THREAD              -3107 // 创建本地数据接收线程出错
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_CREATE_FIND_THREAD                      -3108 // 创建本地数据发现线程出错
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SUB_FRAME_INDEX_ERROR                   -3109 // 子帧序号不对
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SEND_ERROR                              -3110 // 发送出错
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SUB_FRAME_NUM_ERROR                     -3111 // 子帧数量不对
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_CREATE_DATA_RECIEVE_THREAD_CTRL_PIPE    -3112 // 创建本地数据接收线程控制管道出错
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SOCKET_OPT_ERROR                        -3113 // 本地连接sock opt错误
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_INIT_SEM_ERROR                          -3114 // 初始化信号量错误

#define IPP_ERROR_CODE_LINK_LAYER_CLOUD_CREATE_XMPP_MAIN_THREAD                 -3115 // 创建云平台XMPP主线程

#endif /* IPP2_COMMON_ERROR_CODE_H_ */
