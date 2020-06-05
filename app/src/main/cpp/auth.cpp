#include <jni.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close


#define BUFFER_SIZE 1024


void dialog(JNIEnv *pEnv, jclass pJclass, jobject pJobject);

extern "C"
JNIEXPORT void JNICALL
Java_com_auth_check_AuthCheck_nativecheck(JNIEnv *env, jclass clazz, jobject context) {


    dialog(env,clazz,context);

}

void dialog(JNIEnv *env, jclass clazz, jobject context) {


    // AlertDialog.Builder builder = new AlertDialog.Builder(context);
    jclass jclass_AlertDialogBuilder = env->FindClass("android/app/AlertDialog$Builder");
    jmethodID jmethod_tem = env->GetMethodID(jclass_AlertDialogBuilder, "<init>",
                                             "(Landroid/content/Context;)V");
    jobject jobject_AlertDialogBuilder = env->NewObject(jclass_AlertDialogBuilder, jmethod_tem,
                                                        context);

    // builder.setTitle("text"); public Builder setTitle(java.lang.CharSequence message)
    jmethod_tem = env->GetMethodID(jclass_AlertDialogBuilder, "setTitle",
                                   "(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(jobject_AlertDialogBuilder, jmethod_tem, env->NewStringUTF("权限提示"));

    // builder.setMessage("text"); public Builder setMessage(CharSequence message)
    jmethod_tem = env->GetMethodID(jclass_AlertDialogBuilder, "setMessage",
                                   "(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(jobject_AlertDialogBuilder, jmethod_tem, env->NewStringUTF("鉴权失败"));

    // builder.setPositiveButton("确定", null);
//     public Builder setPositiveButton(CharSequence text, final android.content.DialogInterface.OnClickListener listener)
//    jmethod_tem = env->GetMethodID(jclass_AlertDialogBuilder, "setPositiveButton",
//                                   "(Ljava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)Landroid/app/AlertDialog$Builder;");
//
//    jclass classAuth = env->GetObjectClass(clazz);
//    if (classAuth == NULL)
//        return;
//    jfieldID mListenerFiledID = env->GetFieldID(clazz, "onClickListener",
//                                                "Landroid/content/DialogInterface$OnClickListener;");
//
//    if (mListenerFiledID == NULL)
//        return;
//
//    jobject mListenerFiled =  env->GetObjectField(classAuth,mListenerFiledID);
//
//    if (mListenerFiled == NULL)
//        return;
//
//    env->CallObjectMethod(jobject_AlertDialogBuilder, jmethod_tem, env->NewStringUTF("确定"),
//                          mListenerFiled);

//    env->DeleteLocalRef(classAuth);


    jmethod_tem = env->GetMethodID(jclass_AlertDialogBuilder, "setCancelable",
                                   "(Z)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(jobject_AlertDialogBuilder, jmethod_tem, false);


    // builder.show();  public AlertDialog show()
    jmethod_tem = env->GetMethodID(jclass_AlertDialogBuilder, "show",
                                   "()Landroid/app/AlertDialog;");
    env->CallObjectMethod(jobject_AlertDialogBuilder, jmethod_tem);
}


int create_client(const char *host, int port) {
    struct hostent *he;
    struct sockaddr_in server_addr;
    int socket_fd;

    if ((he = gethostbyname(host)) == NULL) {
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = *((struct in_addr *) he->h_addr);

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        return -1;
    }

    if (connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1) {
        return -1;
    }

    return socket_fd;
}


//char *http_get(const char *url) {
//
//    char post[BUFFER_SIZE] = {'\0'};
//    int socket_fd = -1;
//    char lpbuf[BUFFER_SIZE * 4] = {'\0'};
//    char *ptmp;
//    char host_addr[BUFFER_SIZE] = {'\0'};
//    char file[BUFFER_SIZE] = {'\0'};
//    int port = 0;
//    int len = 0;
//
//    if (!url) {
//        printf("      failed!\n");
//        return NULL;
//    }
//
//    if (http_parse_url(url, host_addr, file, &port)) {
//        printf("http_parse_url failed!\n");
//        return NULL;
//    }
//    //printf("host_addr : %s\tfile:%s\t,%d\n",host_addr,file,port);
//
//    socket_fd = create_client(host_addr, port);
//    if (socket_fd < 0) {
//        printf("http_tcpclient_create failed\n");
//        return NULL;
//    }
//
//    sprintf(lpbuf, HTTP_GET, file, host_addr, port);
//
//    if (http_tcpclient_send(socket_fd, lpbuf, strlen(lpbuf)) < 0) {
//        printf("http_tcpclient_send failed..\n");
//        return NULL;
//    }
//    //	printf("发送请求:\n%s\n",lpbuf);
//
//    if (http_tcpclient_recv(socket_fd, lpbuf) <= 0) {
//        printf("http_tcpclient_recv failed\n");
//        return NULL;
//    }
//    http_tcpclient_close(socket_fd);
//
//    return http_parse_result(lpbuf);
//}