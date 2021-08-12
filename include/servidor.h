#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "canaltexto.h"

class Servidor{
	private:

        int usuarioDonoId; // Id do usuário que criou o servidor
        std::string nome; // nome do servidor
        std::string descricao;
        std::string codigoConvite;

        std::vector<CanalTexto> canaisTexto;
        std::vector<int> participantesIDs;

    public:

    void set_uDI (int usuarioDonoId_) { usuarioDonoId = usuarioDonoId_; };
    int get_uDI () { return usuarioDonoId; };

    void set_nome (const std::string nome_) { nome = nome_; };
    std::string get_nome () { return nome; };

    void set_descricao (const std::string descricao_) { descricao = descricao_; };
    std::string get_descricao () { return descricao; };

    void set_codigoC (const std::string codigoConvite_) { codigoConvite = codigoConvite_; };
    std::string get_codigoC () { return codigoConvite; };

    void add_to_cT (CanalTexto canal) { canaisTexto.push_back(canal); };
    size_t get_tam_cT () { return canaisTexto.size(); };
    CanalTexto get_cT_n (int n) { return canaisTexto[n]; };

    void add_to_pIDs (int id_p) { participantesIDs.push_back(id_p); };
    size_t get_pIDs_size () { return participantesIDs.size(); };
    int get_pIDs_n (int n) { return participantesIDs[n]; };
    void remove_ID (int id_)
    {
        for (int a = 0; a < participantesIDs.size(); a++)
        {
            if (participantesIDs[a] == id_)
            {
                participantesIDs.erase(participantesIDs.begin() + a);
            }
        }
    }
    bool check_member (int id_)
    {
        for (int a = 0; a < participantesIDs.size(); a++)
        {
            if (participantesIDs[a] == id_)
            {
                return true;
            }
        }

        return false;
    }
};

#endif
