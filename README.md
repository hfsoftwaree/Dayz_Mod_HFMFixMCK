# 📋 HFMFixMCK – Log de Veículos para o HF Manager

Mod de **scripts (Enforce Script)** para **DayZ Standalone** que gera **logs detalhados de veículos** integrados ao **MuchCarKey (MCK)**. Ele foi desenvolvido para uso com o **HF Manager**, sistema de gerenciamento de servidores DayZ desenvolvido em **Delphi**, que consome esses logs.

https://github.com/hfsoftwaree/HFManagerUpdate

---

## 📦 Dependência

- **MuchCarKey (MCK)**: usado para obter o ID do veículo (`MCK_Transport.GetTransportId`) e o tempo restante até o despawn.

> Veículos que ainda não possuem ID do MCK não são registrados nos eventos de ação.

---

## ✨ Funcionalidades

O mod registra, em um arquivo de log no servidor, os seguintes eventos:

| Evento | Informações registradas |
|---|---|
| 🚗 Inicialização de veículo / barco no mapa | Nome, classe, ID do MCK, posição e tempo de vida restante |
| 🚪 Entrada no veículo | Jogador, posição, veículo, ID e assento (motorista, co-piloto, passageiros) |
| 🚪 Saída do veículo | Jogador, posição, veículo e ID |
| 🔑 Motor ligado / desligado | Jogador, posição, veículo e ID |
| 🫸 Veículo empurrado | Jogador, posição, veículo e ID |
| 💥 Veículo destruído | Veículo, ID, posição, autor do dano e item usado |
| 🗑️ Veículo removido (`EEDelete`) | Veículo, ID, posição e tempo de vida restante no banco |

Todo o registro de ações roda **apenas no servidor** (`#ifdef SERVER`).

---

## 📄 Arquivo de log

Os logs são gravados na pasta de perfil do servidor (`$profile:`), com um arquivo novo a cada inicialização:

```
HFM_Vehicles_FixMck_AAAA-MM-DD_HH-MM-SS.log
```

Exemplo de saída:

```
Log Created: _2026-11-24_10-30-00
10:31:02 | Vehicle in map: Sedan [CivilianSedan] (ID: 12 - pos <7500, 300, 7600>) initialized. Remaining lifetime: 5 dias
10:35:10 | Player Jogador1 (<7500, 300, 7600>) entered in vehicle Sedan [CivilianSedan] (ID: 12) on Driver seat
10:35:12 | Player Jogador1 (<7500, 300, 7600>) started vehicle Sedan [CivilianSedan] (ID: 12)
10:40:55 | Sedan [CivilianSedan] (ID: 12 - pos <7510, 300, 7620>) has been destroyed by: Jogador2 using M4A1
```

---

## 🔗 Integração com o HF Manager

O HF Manager lê esses arquivos para dar visibilidade aos administradores sobre o ciclo de vida dos veículos: onde estão, quem os usou, quando foram destruídos ou removidos.

---

## ⚙️ Como funciona

O mod usa `modded class` para estender:

- `CarScript` e `BoatScript`: log de inicialização, destruição (`EEHitBy`) e remoção (`EEDelete`)
- `ActionGetInTransport` / `ActionGetOutTransport`: entrada e saída
- `ActionStartEngine` / `ActionStopEngine`: motor ligado e desligado
- `ActionPushObject`: empurrar veículo
- `MissionServer`: criação do arquivo de log ao iniciar o servidor

---

## 📁 Estrutura do projeto

```
HFMFixMck/
├── config.cpp
└── scripts/
    ├── 4_World/
    └── 5_Mission/
```

---

## 🧰 Tecnologias

- Enforce Script (DayZ)
- MuchCarKey API
- Delphi (HF Manager, sistema que consome os logs)

---

## 👤 Autor

Desenvolvido por **HF**.

