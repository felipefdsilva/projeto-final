# projeto-final
Protocolo para monitoramento de visitantes de uma parque florestal utilizando LoRa

Próximos Passos:

- Aprimorar interface a classe Message
  - A mensagem é representada de três formas
    - array de fields
    - array de 16 bits ou bytes duplos (?)
    - array de bytes (forçada pela interface do RadioHead)
  - Fazer um construtor para cada caso? Facilitaria?
  - Melhorar nome das funções
  - Encapsular melhor as conversões
    - por exemplo, converter de byte duplo para byte dentro da função de envio (?)
    - ou já no construtor, salvar nas duas representações (Fields e Byte)
    - usar os bytes duplos apenas como um caminho intermediário (?)
- Aprimorar interface http para testes locais
    - Entender como reutilizar o socket (?)
    - Atualmente é fácil trocar um mensagem, para um mero reply utilizando as funções definidas "quebra" o código

- Testar troca de duas mensagens, com nós fazendo ambos os papeis (receiver e sender)
- Implementar aos poucos a maquina de estados terminal x terminal