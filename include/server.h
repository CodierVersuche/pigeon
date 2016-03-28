//
// Created by kamlesh on 16/10/15.
//

#ifndef PIGEON_SERVER_H
#define PIGEON_SERVER_H


#include "http_handler_base.h"
#include "http_filter_base.h"

using namespace std;

namespace pigeon {



    class server {

    private:
        class server_impl;
        server_impl* _Impl;

    public:

        server();
        ~server();
        void start();

    };



}

#endif //PIGEON_SERVER_H
