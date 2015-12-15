#ifndef _IPP_ERROR_CODE_H_
#define _IPP_ERROR_CODE_H_

#define IPP_ERROR_CODE_SUCCESS                                                  0     // �ɹ�

#define IPP_ERROR_CODE_COMMON_PROBUF_PROBUF_IS_NULL                             -1    // IPP Protocol BufferΪ��
#define IPP_ERROR_CODE_COMMON_PROBUF_BUF_IS_NULL                                -2    // BufferΪ��
#define IPP_ERROR_CODE_COMMON_PROBUF_BUF_NOT_ENOUGH                             -3    // IPP Protocol Buffer�ռ䲻��
#define IPP_ERROR_CODE_COMMON_TIMER_SET_SELECT_ERROR                            -4    // ��ʱ��SELECT���ô���
#define IPP_ERROR_CODE_COMMON_CREATE_TIMER_THREAD_ERROR                         -5    // ������ʱ���̴߳���
#define IPP_ERROR_CODE_COMMON_TIMER_IS_NOT_OVER                                 -6    // ��ʱ��δ����
#define IPP_ERROR_CODE_COMMON_CREATE_TIMER_PIPE_ERROR                           -7    // ������ʱ���ܵ�����
#define IPP_ERROR_CODE_COMMON_PROBUF_ASCII_STR_IS_NULL                          -8    // buf��Ϊ��
#define IPP_ERROR_CODE_COMMON_PROBUF_ASCII_STR_SIZE_ERROR                       -9    // buf�����ȴ���
#define IPP_ERROR_CODE_COMMON_ALLOC_FILED										-10   // �����ڴ�ʧ��

#define IPP_ERROR_CODE_BUSINESS_LAYER_PROFILE_CONFIG_IS_FULL                    -1101 // IPP profile����Ϊ��
#define IPP_ERROR_CODE_BUSINESS_LAYER_EVENT_DISPATCHER_IS_FULL                  -1102 // �¼�������Ϊ��
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_REQUEST_DISPATCHER_IS_FULL        -1103 // �������������Ϊ��
#define IPP_ERROR_CODE_BUSINESS_LAYER_DISPATCHE_SERVICE_REQUEST_ERROR           -1104 // ��������������
#define IPP_ERROR_CODE_BUSINESS_LAYER_DISPATCHE_EVENT_HANDLER_NULL              -1105 // �¼����䴦����Ϊ��
#define IPP_ERROR_CODE_BUSINESS_LAYER_DISPATCHE_SERVICE_REQUEST_HANDLER_NULL    -1106 // ����������䴦����Ϊ��
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_REQUEST_HANDLER_SET_NULL          -1107 // ��������������Ϊ��
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_REQUEST_HANDLER_NULL              -1108 // ������������Ϊ��
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_GET_OBJ_CLASS_ERROR           -1109 // JNI��ȡ�������ͳ���
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_GET_GJVM_ERROR                -1110 // JNI��ȡ���������
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_SET_GOBJ_ERROR                -1111 // JNI����ȫ�ֶ������
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_SET_GCLS_ERROR                -1112 // JNI����ȫ�������
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_ATTACH_THREAD_ERROR           -1113 // JNI�����߳�
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_DETACH_THREAD_ERROR           -1114 // JNIȡ�������߳�
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_GET_METHOD_ID_ERROR           -1115 // JNI��ȡ����ID
#define IPP_ERROR_CODE_BUSINESS_LAYER_SERVICE_JNI_CALL_METHOD_EXP               -1116 // JNI���÷��������쳣
#define IPP_ERROR_CODE_BUSINESS_LAYER_DEVICE_IMPL_HADLE_SERVICE_REQ_NULL        -1117 // device imple service request null

#define IPP_ERROR_CODE_DEVICE_LAYER_NEW_DEVICE_EVENT_RECIEVE_QUEUE              -2101 // �������ն��г���
#define IPP_ERROR_CODE_DEVICE_LAYER_CREATE_HANDLE_DEVICE_EVENT_THREAD           -2102 // ���������̳߳���
#define IPP_ERROR_CODE_DEVICE_LAYER_RECIEVE_DEVICE_EVENT_NULL                   -2103 // �����豸�¼�Ϊ��
#define IPP_ERROR_CODE_DEVICE_LAYER_RECIEVE_DEVICE_QUEUE_IS_FULL                -2104 // �����豸�¼�������
#define IPP_ERROR_CODE_DEVICE_LAYER_RECIEVE_DEVICE_CONFIG_IS_FULL               -2105 // IPP�¼���������Ϊ��
#define IPP_ERROR_CODE_DEVICE_LAYER_CALL_SERVICE_LINK_INFO_NULL                 -2106 // ���ʷ���������Ϣ��
#define IPP_ERROR_CODE_DEVICE_LAYER_LINK_LAYER_CONFIG_NULL                      -2107 // ���Ӳ�����Ϊ��
#define IPP_ERROR_CODE_DEVICE_LAYER_CALL_SERVICE_NO_CONFIG                      -2108 // �޵��÷�������
#define IPP_ERROR_CODE_DEVICE_LAYER_CALL_SERVICE_ID_ERROR                       -2109 // ���÷���ID����
#define IPP_ERROR_CODE_DEVICE_LAYER_CALL_SERVICE_LINK_TYPE_ERR                  -2110 // ���ʷ�����Ϣ���Ͳ�ƥ��
#define IPP_ERROR_CODE_DEVICE_LAYER_NEW_DEVICE_EVENT_SEND_QUEUE                 -2111 // �������Ͷ��г���
#define IPP_ERROR_CODE_DEVICE_LAYER_CREATE_SEND_DEVICE_EVENT_THREAD             -2112 // ���������̳߳���
#define IPP_ERROR_CODE_DEVICE_LAYER_SEND_DEVICE_EVENT_NULL                      -2113 // �����豸�¼�Ϊ��
#define IPP_ERROR_CODE_DEVICE_LAYER_SEND_DEVICE_QUEUE_IS_FULL                   -2114 // �����豸�¼�������
#define IPP_ERROR_CODE_DEVICE_LAYER_SEND_EVENT_LINK_INFO_NULL                   -2115 // �����¼���������Ϣ��
#define IPP_ERROR_CODE_DEVICE_LAYER_SEND_EVENT_LINK_TYPE_ERR                    -2116 // �����¼�����Ϣ���Ͳ�ƥ��
#define IPP_ERROR_CODE_DEVICE_LAYER_NEW_DEVICE_SERVICE_REQUEST_QUEUE            -2117 // ��������������г���
#define IPP_ERROR_CODE_DEVICE_LAYER_CREATE_HANDLE_DEVICE_SERVICE_REQUEST_THREAD -2118 // �������������̳߳���
#define IPP_ERROR_CODE_DEVICE_LAYER_BE_CALLED_DEVICE_SERVICE_NULL               -2119 // �豸���񱻵���Ϊ��
#define IPP_ERROR_CODE_DEVICE_LAYER_DEVICE_SERVICE_REQUEST_QUEUE_IS_FULL        -2120 // �����豸�������������
#define IPP_ERROR_CODE_DEVICE_LAYER_SEND_SERVICE_RESPONSE_NO_CONFIG             -2121 // �޵��÷��͵��÷�������
#define IPP_ERROR_CODE_DEVICE_LAYER_CALL_SERVICE_TIMEOUT                        -2122 // ���÷���ʱ
#define IPP_ERROR_CODE_DEVICE_LAYER_CHECK_SERVICE_RESPONSE_NOT_MATCH            -2123 // ����������ƥ��
#define IPP_ERROR_CODE_DEVICE_LAYER_CERTIFICATE_CONTROL_IN_LIST_NULL            -2124 // ��֤���ƶˣ����б���Ϊ��
#define IPP_ERROR_CODE_DEVICE_LAYER_SERVICE_REQUEST_CONFIG_IS_FULL              -2125 // IPP������������Ϊ��
#define IPP_ERROR_CODE_DEVICE_LAYER_INIT_SEM_ERROR                              -2126 // ��ʼ���ź�������
#define IPP_ERROR_CODE_DEVICE_LAYER_CONTROL_IS_NOT_CERTIFICATED                 -2127 // ���ƶ�δ��֤

#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_LINK_SPECIFIC_NULL                      -3101 // ��������������Ϣ��
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_PROTOCOL_BUFFER_NULL                    -3102 // ��������protocol buffer��
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SOCKET_ERROR                            -3103 // ��������sock����
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SENDTO_ERROR                            -3104 // ��������sendto����
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_MAX_RESEND_TIMES                        -3105 // �������Ӵﵽ�ط�����
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_NEW_DATA_RECIEVE_QUEUE                  -3106 // �������ؽ������ݶ��г���
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_CREATE_DATA_RECIEVE_THREAD              -3107 // �����������ݽ����̳߳���
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_CREATE_FIND_THREAD                      -3108 // �����������ݷ����̳߳���
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SUB_FRAME_INDEX_ERROR                   -3109 // ��֡��Ų���
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SEND_ERROR                              -3110 // ���ͳ���
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SUB_FRAME_NUM_ERROR                     -3111 // ��֡��������
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_CREATE_DATA_RECIEVE_THREAD_CTRL_PIPE    -3112 // �����������ݽ����߳̿��ƹܵ�����
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_SOCKET_OPT_ERROR                        -3113 // ��������sock opt����
#define IPP_ERROR_CODE_LINK_LAYER_LOCAL_INIT_SEM_ERROR                          -3114 // ��ʼ���ź�������

#define IPP_ERROR_CODE_LINK_LAYER_CLOUD_CREATE_XMPP_MAIN_THREAD                 -3115 // ������ƽ̨XMPP���߳�

#endif /* IPP2_COMMON_ERROR_CODE_H_ */
