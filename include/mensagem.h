#ifndef MENSAGEM_H
#define MENSAGEM_H

class Mensagem{
    private:

        std::string dataHora;
        int enviadaPor;
        std::string conteudo;

    public:

        void set_dataHora (char * datahora_){ dataHora.append(datahora_); };
        std::string get_dataHora () { return dataHora; };

        void set_enviadaPor (int enviadaPor_) { enviadaPor = enviadaPor_; };
        int get_enviadaPor () { return enviadaPor; };

        void set_conteudo (std::string conteudo_) { conteudo = conteudo_; };
        std::string get_conteudo () { return conteudo; };

};

#endif
