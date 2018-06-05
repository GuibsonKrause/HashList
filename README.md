# HashList

Primeiro Trabalho de TPA – Tabelas Hash
Objetivos:
•
•
•
•
•
Implementar uma biblioteca de listas
Implementar hash fechada e hash aberta;
Praticar o reuso de bibliotecas;
Praticar o uso de ponteiros;
Avaliar a complexidade dos algoritmos de busca em hash comparando os tempos de busca com
os tempos de busca em listas.
Especificações do programa
1. Arquivos de entrada
Seu programa deverá receber como entrada um arquivo gerado pelo programa de geração de
arquivos disponibilizado como parte deste trabalho. Este programa gera arquivos contendo dados
sobre contatos (pessoas) fictícios.
Para gerar arquivos de entrada rode o programa no prompt digitando o nome do programa seguido
pela quantidade de contatos a serem geradas, por exemplo: geraArquivo.exe 100000
Será gerado um arquivo nomeado entrada.txt. Cada linha do arquivo trará os seguintes dados de um
“contato”: nome e telefone. Esses dados são separados por ; (ponto e vírgula).
Além do entrada.txt será gerado um arquivo chamado operações.txt. Cada linha deste arquivo
representa uma operação a ser efetuada pelo seu programa. A operação é representada pelo
primeiro caracter da linha.
a. Caso a linha inicie com “E”, representa uma ordem de exclusão. A letra “E” será seguida
por um ponto-e-virgula e pelo nome do contato a ser excluído.
b. Caso a linha inicie com “I”, representa uma inclusão. A letra “I” será seguida por um
ponto-e-virgula e pelos dados do contato, ou seja, nome e telefone do contato
separados por ponto-e-virgula.
c. Caso a linha inicie com “B”, representa uma busca. A letra “B” será seguida por um
ponto-e-virgula acompanhado pelo nome e pelo telefone do contato, separados por
ponto-e-virgula.
2. Leitura do arquivo entrada.txt e geração, em memória, da lista e das tabelas hash
Seu programa deve ler o arquivo entrada.txt gerando, a cada linha lida, um registro de contato. Esse
registro deve ser então inserido em 3 estruturas distintas:
a. Uma lista ordenada por nome;
b. Uma hash aberta utilizando o telefone do contato como chave.
i. Inicie a hash com tamanho 100000, use load factor de 95% e sempre que for
expandir, aumente o tamanho em 100000.
ii. Utilize a função hash que desejar;c. Uma hash fechada utilizando o nome do contato como chave
i. Cada índice da hash deve conter uma lista ordenada a fim de tratar as colisões.
Aqui você deve reutilizar a estrutura de lista.
ii. Utilize a função hash que desejar, considerando que sua tabela hash deve ter,
ao menos, 1000 índices.
3. Leitura do arquivo operacoes.txt e geração dos arquivos de saída.
Depois de ler o arquivo gerando as estruturas em memória vc deve ler o arquivo operacoes.txt. Para
cada linha deste arquivo você deve:
a. Se a linha se iniciar com “E”:
i. Leia o nome que acompanha a letra E, e elimine da lista e das duas tabelas hash
os registros de todos os contatos com o nome informado.
ii. Pode haver mais de um contato com o mesmo nome!
iii. Dica: Lembre-se de desalocar o contato depois de eliminá-lo de todas as
estruturas.
b. Se a linha se iniciar com a letra “I”:
i. Obtenha os dados da contato a ser inserido, gere o registro do contato e insira
em todas as estruturas, seguindo o mesmo procedimento que fez na leitura do
arquivo inicial.
c. Se a linha se iniciar com a letra “B”:
i. Leia o nome e o telefone que acompanham a letra “B”.
ii. Busque na lista e na hash fechada pelo primeiro contato que tiver o nome
solicitado, contando quantos elementos foram verificados na busca em cada
uma das estruturas.
iii. Na hash aberta busque pelo primeiro contato que tiver o telefone solicitado,
também contando a quantidade de elementos verificados.
iv. Seu programa deve gerar um arquivo de saída, chamado “buscas.txt” que terá
uma linha para cada busca, contendo os seguintes dados separados por ponto-
e-virgula:
1. Nome do contato pesquisado
2. Telefone do contato pesquisado
3. Flag indicando se encontrou ou não o registro na lista (0 se não
encontrar e 1 se encontrar)
4. Quantidade de contatos comparados até encontrar o elemento na lista
(ou até concluir que o elemento não existe, no caso de não encontrar).
5. Flag indicando se encontrou ou não o registro da hash fechada (0 se não
encontrar e 1 se encontrar)
6. Quantidade de contatos comparados até encontrar o elemento na hash
fechada (ou até concluir que o elemento não existe, no caso de não
encontrar).
7. Flag indicando se encontrou ou não o registro na hash aberta (0 se não
encontrar e 1 se encontrar)8. Quantidade de contatos comparados até encontrar o elemento na hash
aberta (ou até concluir que o elemento não existe, no caso de não
encontrar).
v. Por exemplo, suponha que o registro de nome “Zé” e telefone “27999988822”
não tenha sido encontrado em nenhuma das estruturas e tenha comparado
com 300 contatos para chegar à conclusão de que o elemento não existe na
lista, comparado com 30 contatos na hash aberta e com 20 contatos na hash
fechada. Nesse caso, deve ser gerada a seguinte linha no arquivo de saída:
Zé;27999988822;0;300;0;30;0;20
OBS.: Tendo em vista que o mesmo arquivo será utilizado para alimentar todas as
estruturas, se um elemento for encontrado em uma estrutura, deveria ser encontrado também em
todas as outras.
4. Geração de arquivos de saída
Agora seu programa deve gerar dois arquivos de saída, mostrando o conteúdo das tabelas hash:
a. O primeiro deve ser nomeado saidaHashAberta.txt.
i. Para gerar esse arquivo faça uma varredura na hash aberta iniciando do índice
zero até o índice máximo, gerando uma linha no arquivo para cada contato.
ii. Cada linha dessas deve conter: o índice do contato na hash aberta, o nome do
contato, o telefone do contato e um flag com a seguinte codificação: 1 se o
contato está no índice referente a seu hash code, ou seja, não sofreu colisão e 0
se o contato está em índice diferente do seu hash code, ou seja, houve colisão.
Os dados devem sempre ser separados por ponto-e-virgula (;)
iii. Por fim, a última linha do arquivo deve ser composta por 2 números inteiros
separados por ponto e vírgula: a quantidade de elementos que não sofreram
colisão e o número de elementos que foram deslocados por colisão.
b. O segundo arquivo deve ser nomeado saidaHashFechada.txt.
i. Para gerar esse arquivo faça uma varredura na hash fechada iniciando do índice
zero até o índice máximo. Para cada índice, varra a lista de elementos do índice,
do primeiro ao último elemento, gerando uma linha no arquivo para cada
contato.
ii. Cada linha dessas deve conter: o índice do contato na hash fechada, o nome do
contato e o telefone do contato. Os dados devem sempre ser separados por
ponto-e-virgula (;).
iii. A última linha do arquivo deve conter o índice e a quantidade de elementos que
estava em cada índice da hash (separados por ponto e vírgula). Por exemplo,
suponha uma hash fechada de 3 posições que tenha 12 contatos na lista do
índice 0, 20 contatos na lista do índice 1 e 18 contatos na lista do índice 2. Nesse
caso a última linha do arquivo seria:
0;12;1;20;2;18
Requisitos não-funcionais•
•
•
Crie bibliotecas de listas e de tabelas hash;
Reutilize a biblioteca de listas para implementar os métodos de hash fechada;
Apesar de manter 3 estruturas de dados contendo os dados dos contatos, esses dados não
devem ser replicados. Ou seja, você deve alocar apenas um registro de contato em memória e
inserir esse registro em todas as estruturas. Assim, todas as estruturas de dados devem apontar
para os mesmos registros de contato.
Relatório
Faça um relatório contendo:
1. Avaliação da ordem de complexidade das buscas em lista não ordenada, hash fechada e hash
aberta, Ilustrando a análise com trechos do seu código e exemplificando com resultados da
execução dos arquivos de busca.
2. Explique as funções hash que você implementou para a hash aberta e para a hash fechada.
Analise se a escolha foi boa considerando a distribuição dos contatos pelos índices das tabelas
(utilize os dados gerados nos arquivos de saída para ilustrar a discussão.)
Entrega
Deve ser entregue um arquivo compactado contendo:
•
•
Os códigos fontes (programa principal + bibliotecas)
Relatório
O trabalho deve ser entregue até 17/04/2017. O prazo final não será adiado em hipótese alguma.
Valor: 15 pontos (15% da nota semestral).
Eventuais alterações nas especificações serão comunicadas durantes as aulas e formalizadas pela
substituição deste arquivo de especificações no Moodle. Assim, antes de submeter seu trabalho
certifique-se de que está atendendo às especificações mais recentes!
