#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario{

    private:

	int id; // identificador
	std::string email;
	std::string senha;
	std::string nome; // nome (com espaços)

    public:

    void set_id (int id_) { id = id_; };
    int get_id () { return id; };

    void set_email (const std::string email_) { email = email_; };
    std::string get_email () { return email; };

    void set_senha (const std::string senha_) { senha = senha_; };
    std::string get_senha () { return senha; };

    void set_nome (const std::string nome_) { nome = nome_; };
    std::string get_nome () { return nome; };
};

#endif
