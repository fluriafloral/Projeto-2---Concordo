#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <time.h>

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  Usuario cadastro;

  if (usuarios.size() == 0)
  {
    cadastro.set_id(usuarios.size());
    cadastro.set_email(email);
    cadastro.set_senha(senha);
    cadastro.set_nome(nome);

    usuarios.push_back(cadastro);
    return "Usuário criado";
  }
  else
  {
    for (int a = 0; a < usuarios.size(); a++)
    {
        if (usuarios[a].get_email() == email)
        {
            return "Usuário já existe !";
        }
    }

    cadastro.set_id(usuarios.size());
    cadastro.set_email(email);
    cadastro.set_senha(senha);
    cadastro.set_nome(nome);

    usuarios.push_back(cadastro);
    return "Usuário criado";
  }
}

string Sistema::login(const string email, const string senha) {
  for (int a = 0; a < usuarios.size(); a++)
  {
    if ((usuarios[a].get_email() == email) && (usuarios[a].get_senha() == senha))
    {
        usuariosLogados.insert({usuarios[a].get_id(),{NULL, NULL}});

        return "Logado como : " + email;
    }
  }

  return "Senha ou usuário inválidos !";
}

string Sistema::disconnect(int id) {
  for (auto it = usuariosLogados.begin(); it != usuariosLogados.end(); it++)
  {
    if (it->first == id)
    {
        it = usuariosLogados.erase(it);

        return "Desconectando usuário " + usuarios[id].get_email();
    }
  }

  return "Não está conectado";
}

string Sistema::create_server(int id, const string nome) {
  if (usuariosLogados.find(id) == usuariosLogados.end())
  {
    return "usuário não está logado!";
  }

  Servidor new_server;

  if (servidores.size() == 0)
  {
    new_server.set_uDI(id);
    new_server.set_descricao("descricao");
    new_server.set_codigoC("");
    new_server.set_nome(nome);

    new_server.add_to_pIDs(id);

    auto it = usuariosLogados.begin();

    if (it->first == id)
    {
        it->second = {&new_server, NULL};
    }

    servidores.push_back(new_server);

    return "Servidor criado";
  }
  else
  {
    for (int a = 0; a < servidores.size(); a++)
    {
        if (servidores[a].get_nome() == nome)
        {
            return "Servidor com esse nome já existe !";
        }
    }

    new_server.set_uDI(id);
    new_server.set_descricao("descricao");
    new_server.set_codigoC("");
    new_server.set_nome(nome);

    new_server.add_to_pIDs(id);

    servidores.push_back(new_server);

    usuariosLogados.at(id).first = &new_server;

    return "Servidor criado";
  }
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  if (usuariosLogados.find(id) == usuariosLogados.end())
  {
    return "usuário não está logado!";
  }

  for (int a = 0; a < servidores.size(); a++)
  {
    if (servidores[a].get_nome() == nome)
    {
        if (servidores[a].get_uDI() == id)
        {
            servidores[a].set_descricao(descricao);

            return "Descrição do servidor '" + nome + "' modificada!";
        }
        else
        {
            return "Você não pode alterar a descrição de um servidor que não foi criado por você";
        }
    }
  }

  return "Servidor '" + nome + "' não existe";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  if (usuariosLogados.find(id) == usuariosLogados.end())
  {
    return "usuário não está logado!";
  }

  for (int a = 0; a <= servidores.size(); a++)
  {
    if (servidores[a].get_uDI() == id)
    {
        if (servidores[a].get_nome() == nome)
        {
            servidores[a].set_codigoC(codigo);

            if (codigo == "")
            {
                return "Código de convite do servidor '" + nome + "' removido!";
            }

            else
            {
                return "Código de convite do servidor '" + nome + "' modificado!";
            }
        }

        else
        {
            return "O nome do servidor está incorreto OU ele é inexistente";
        }
    }
  }

  return "Você não pode alterar o código de convite de um servidor que não foi criado por você";
}

string Sistema::list_servers(int id) {
  if (usuariosLogados.find(id) == usuariosLogados.end())
  {
    return "usuário não está logado!";
  }

  string str;

  for (int a = 0; a < servidores.size(); a++)
  {
    str = str + servidores[a].get_nome() + " \n";
  }
  return str;
}

string Sistema::remove_server(int id, const string nome) {
  if (usuariosLogados.find(id) == usuariosLogados.end())
  {
    return "usuário não está logado!";
  }

  for (int a = 0; a < servidores.size(); a++)
  {
    Servidor s = servidores[a];

    if (s.get_nome() == nome)
    {
        if (s.get_uDI() != id)
        {
            return "Você não é o dono do servidor '" + nome + "'";
        }

        for (int b = 0; b < usuarios.size(); b++)
        {
            if (s.check_member(usuarios[b].get_id()) == true)
            {
                usuariosLogados.at(usuarios[b].get_id()).first = NULL;
            }
        }

        servidores.erase(servidores.begin() + a);

        return "Servidor '" + nome + "' removido com sucesso";
    }
  }

  return "Servidor '" + nome + "' não encontrado";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  if (usuariosLogados.find(id) == usuariosLogados.end())
  {
    return "usuário não está logado!";
  }

  int s;

  for (size_t a = 0; a < servidores.size(); a++)
  {
    if (servidores[a].get_nome() == nome)
    {
        s = a;

        break;
    }
    if (a == servidores.size() - 1 && servidores[a].get_nome() != nome)
    {
        return "Servidor '" + nome + "' não encontrado";
    }
  }

  if (servidores[s].get_uDI() == id)
  {
    usuariosLogados.at(id).first = &servidores[s];

    return "Entrou no servidor com sucesso";
  }
  else
  {
    if (servidores[s].get_codigoC() == "")
    {
        if (servidores[s].check_member(id) == false)
        {
            servidores[s].add_to_pIDs(id);
        }

        usuariosLogados.at(id).first = &servidores[s];

        return "Entrou no servidor com sucesso";
    }
    else
    {
        if (servidores[s].get_codigoC() == codigo)
        {
            if (servidores[s].check_member(id) == false)
            {
                servidores[s].add_to_pIDs(id);
            }

            usuariosLogados.at(id).first = &servidores[s];

            return "Entrou no servidor com sucesso";
        }
        else if (codigo == "")
        {
            return "Servidor requer código de convite";
        }
        else
        {
            return "Código de contive inválido";
        }
    }
  }

  return "Servidor '" + nome + "' não encontrado";
}

string Sistema::leave_server(int id, const string nome) {
  if (usuariosLogados.find(id) == usuariosLogados.end())
  {
    return "usuário não está logado!";
  }

  int s;

  for (int a = 0; a < servidores.size(); a++)
  {
    if (servidores[a].get_nome() == nome)
    {
        s = a;

        break;
    }
    if ((a == servidores.size() - 1) && (servidores[a].get_nome() != nome))
    {
        return "Servidor '" + nome + "' não encontrado";
    }
  }

  if (servidores[s].check_member(id) == false)
  {
    return "Usuário não é membro do servidor!";
  }
  else
  {
    servidores[s].remove_ID(id);
  }

  if (usuariosLogados.at(id).first == &servidores[s])
  {
    usuariosLogados.at(id).first = NULL;

    return "Saindo do servidor '" + nome + "'";
  }

  if (usuariosLogados.at(id).first == NULL)
  {
    return "Você não está vizualizando nenhum servidor";
  }


  return "Servidor '" + nome + "' não encontrado";
}

string Sistema::list_participants(int id) {
  if (usuariosLogados.find(id) == usuariosLogados.end())
  {
    return "usuário não está logado!";
  }

  int s;
  string str;

  if (usuariosLogados.at(id).first == NULL)
  {
    return "O usuário não vizualiza nenhum servidor!";
  }
  else
  {
    for (int a = 0; a < servidores.size(); a ++)
    {
        if (usuariosLogados.at(id).first == &servidores[a])
        {
            s = a;

            break;
        }
    }
  }

  for (int b = 0; b < usuarios.size(); b++)
  {
    if (servidores[s].check_member(usuarios[b].get_id()) == true)
    {
        str = str + usuarios[b].get_nome() + "\n";
    }
  }

  return str;
}

string Sistema::list_channels(int id) {
  if (usuariosLogados.find(id) == usuariosLogados.end())
  {
    return "usuário não está logado!";
  }

  int s;
  string str;

  for (int a = 0; a < servidores.size(); a++)
  {
    if (usuariosLogados.at(id).first == &servidores[a])
    {
        s = a;

        break;
    }
  }

  for (int b = 0; b < servidores[s].get_tam_cT(); b++)
  {
    str = str + servidores[s].get_cT_n(b).get_nomeCanal() + "\n";
  }

  return str;
}

string Sistema::create_channel(int id, const string nome) {
  CanalTexto ct;
  int s, c;

  for (int a = 0; a < servidores.size(); a++)
  {
    if (usuariosLogados.at(id).first == &servidores[a])
    {
        s = a;

        break;
    }
  }

  for (int b = 0; b < servidores[s].get_tam_cT(); b++)
  {
    if (servidores[s].get_cT_n(b).get_nomeCanal() == nome)
    {
        return "Canal de texto '" + nome + "' já existe!";
    }
  }

  ct.set_nomeCanal(nome);

  servidores[s].add_to_cT(ct);

  return "Canal de texto '" + nome + "' criado com sucesso";
}

string Sistema::enter_channel(int id, const string nome) {
  int s;
  CanalTexto c;

  if (usuariosLogados.at(id).first == NULL)
  {
        return "O usuário não vizualiza nenhum servidor!";
  }
  else
  {
    for (int a = 0; a < servidores.size(); a++)
    {
        if (usuariosLogados.at(id).first == &servidores[a])
        {
            s = a;

            break;
        }
    }
  }

  for (int b = 0; b < servidores[s].get_tam_cT(); b++)
  {
    c = servidores[s].get_cT_n(b);

    if (c.get_nomeCanal() == nome)
    {
        usuariosLogados.at(id).second = &c;

        return "Entrou no canal '" + nome + "' com sucesso";
    }
  }

  return "Canal '" + nome + "' não existe";
}

string Sistema::leave_channel(int id) {
  if (usuariosLogados.at(id).second == NULL)
  {
        return "O usuário não vizualiza nenhum canal!";
  }
  else
  {
    usuariosLogados.at(id).second = NULL;

    return "Saindo do canal";
  }
}

string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
};
