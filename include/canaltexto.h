#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include "mensagem.h"

class CanalTexto{
	private:

        std::string nomeCanal;

        std::vector<Mensagem> mensagens;

    public:

        void set_nomeCanal (std::string nomeCanal_) { nomeCanal = nomeCanal_; };
        std::string get_nomeCanal () { return nomeCanal; };

        int add_to_msgs (Mensagem msg)
        {
            mensagens.push_back(msg);
            return 1;
        };
        size_t get_tam_msgs () { return mensagens.size(); };
        Mensagem get_msg_n (int n) {return mensagens[n]; };
};

#endif
