# TCC-2024

## Monitoramento de Fluxo e Temperatura Interna de uma Colmeia de Abelhas sem Ferrão da Espécie Jandaíra (Melipona subnitida).

A Jandaíra é uma espécie de abelha sem ferrão nativa do Nordeste do Brasil, caracteristicamente encontrada na Caatinga, no Pantanal, e em algumas regiões da Mata Atlântica. Essa abelha desempenha um papel fundamental na rotina de pequenos e médios meliponicultores, contribuindo para sua subsistência ao proporcionar uma fonte adicional de renda, graças aos diversos benefícios econômicos e ambientais que oferece.

Para mais detalhes acesse o documento completo no google drive [Drive](https://docs.google.com/document/d/1YKDgVyDACvofsvOOwmifm7gfQTSiB_c-/edit?usp=sharing&ouid=105124496087722956821&rtpof=true&sd=true).

## Este repositório contém o projeto completo desenvolvido para meu Trabalho de Conclusão de Curso (TCC), que visa monitorar em tempo real o fluxo de abelhas e a temperatura interna de uma colmeia de abelhas sem ferrão, da espécie Jandaíra (Melipona subnitida), utilizando a tecnologia da Internet das Coisas (IoT).

### Estrutura do Projeto
O projeto está organizado em três principais seções: testes iniciais com o Arduino Mega 2560, implementação final com o ESP32, e a interface web para visualização dos dados.

## 1. Testes Iniciais com Arduino Mega 2560
Para os primeiros testes e validação dos componentes, utilizamos o microcontrolador Arduino Mega 2560. Devido à ausência de conectividade nativa com a Internet, essa versão do projeto não inclui funcionalidades IoT. No entanto, foi possível observar e verificar as leituras do sensor de temperatura DS18B20 e do sensor reflexivo E18-D80NK por meio do Monitor Serial e da exibição em tempo real no Display LCD 16x2. Esses testes foram fundamentais para garantir o correto funcionamento dos sensores e o processamento de dados antes de migrar para a versão com IoT.

## 2. Implementação Final com ESP32
A pasta ESP32 contém o código-fonte completo programado em C++ na Arduino IDE para a versão final do projeto, agora integrando a conectividade com a Internet. Utilizando o microcontrolador ESP32, o sistema é capaz de enviar os dados coletados para o banco de dados em tempo real, armazenando as informações no Firebase. Esse avanço possibilita o monitoramento remoto das condições da colmeia, fornecendo ao meliponicultor insights importantes para a tomada de decisões sobre a saúde e o comportamento das abelhas.

Principais Funcionalidades:

Monitoramento contínuo da temperatura interna da colmeia.\
Contagem precisa do fluxo de abelhas entrando e saindo, captada pelo sensor reflexivo.\
Conexão com o Firebase para armazenar e acessar os dados remotamente.\
Visualização de informações essenciais em tempo real no Display LCD 16x2.

## 3. Interface Web - TCC_ABELHAS_2024
A pasta TCC_ABELHAS_2024 contém todos os arquivos relacionados à interface web, desenvolvida para facilitar a visualização dos dados. A interface permite que o usuário monitore a colmeia por meio de gráficos interativos e valores numéricos atualizados em tempo real.

### Destaques da Interface Web:

Exibição gráfica da variação de temperatura ao longo do dia.\
Contagem de fluxo de abelhas apresentada de forma clara e informativa.\
Design responsivo para acesso fácil em diferentes dispositivos.\
Visualização adicional das informações no Display LCD localizado na colmeia, permitindo uma consulta local em caso de falta de acesso à internet.

### Requisitos e Configuração:

Hardware Utilizado: ESP32-WROOM-32, Sensor de Temperatura DS18B20, Sensor Infravermelho Reflexivo Industrial E18-D80NK, Display LCD 16x2 com módulo I2C, entre outros.\
Software e Bibliotecas: Arduino IDE para programação, Firebase para armazenamento de dados, bibliotecas específicas para controle dos sensores e comunicação com a web.

### Considerações Finais:

Este projeto busca promover a sustentabilidade na apicultura ao fornecer uma ferramenta prática e acessível para monitorar colmeias de forma remota. Agradeço a todos que contribuíram para o desenvolvimento deste trabalho, incluindo as valiosas doações de componentes e o suporte técnico recebido.
