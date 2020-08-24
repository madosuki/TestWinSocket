// TestSocket.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <winsock2.h>

int main()
{
    std::cout << "Hello World!\n";

    WSADATA wsaData;
    int error = WSAStartup(MAKEWORD(2, 0), &wsaData);

    if (error != 0) {
        switch (error) {
        case WSASYSNOTREADY:
            printf("Catch WSASYSNOTREADY\nNot ready connect to network\n\n");
            return -1;
        case WSAVERNOTSUPPORTED:
            printf("Catch WSAVENOTSUPPORTED\nthis winsock version is not supported\n\n");
            return -1;
        case WSAEINPROGRESS:
            printf("Catch WSAEINPROGRESS\nstill do block or do callback function on service providor\n\n");
            return -1;
        case WSAEPROCLIM:
            printf("Catch WSAEPROCLIM\narrival to max process number\n\n");
            return -1;
        case WSAEFAULT:
            printf("Catch WSAEFAULT\nsecond argument is invalid pointer\n\n");
            return -1;
        default:
            printf("something error!\n\n");
            return -1;
        }
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == INVALID_SOCKET) {
        printf("socket create failed\n");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;

    int optval = 1;
    // setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));

    bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    listen(sock, 5);

    struct sockaddr_in client;

    while (true) {
        int client_length = sizeof(client);
        SOCKET negotiator = accept(sock, (struct sockaddr*)&client, &client_length);

        char buf[2048];
        memset(buf, 0, sizeof(buf));
        recv(negotiator, buf, sizeof(buf), 0);
        printf("%s\n", buf);

        std::string msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!doctype html><html><head><title>socket test</title></head><body><h1>Yeah!</h1></body></html>";
        send(negotiator, msg.c_str(), msg.size(), 0);



        closesocket(negotiator);
    }

    closesocket(sock);

    WSACleanup();

    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
