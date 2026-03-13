# 📋 Roadmap de Conclusão do Projeto

Este documento detalha os passos sugeridos para completar o **Sistema de Matrícula Acadêmica**, evoluindo de um protótipo básico para um sistema de gerenciamento de dados robusto.

## Fase 1: Finalização do CRUD e Refinamento
Atualmente, o sistema possui operações básicas para Estudantes.
- [ ] **Implementar `StudentDAO::update`**: Permitir a alteração de dados de um estudante existente localizando seu registro por ID e sobrescrevendo os bytes necessários.
- [ ] **Mecanismo de Reuso de Espaço**: Em vez de apenas marcar como removido, implementar uma "Lista Livre" (*Free List*) para reutilizar o espaço de registros excluídos em novos cadastros.
- [ ] **Compactação de Arquivo**: Criar uma função que gere um novo arquivo `.dat` sem os registros marcados como excluídos, otimizando o uso de disco.

## Fase 2: Expansão do Modelo de Dados (DER)
Implementar as entidades restantes conforme a modelagem original:
- [ ] **Professores (`Teacher`)**: Criar modelo e DAO para gerenciamento de docentes.
- [ ] **Cursos e Módulos (`Course` & `Module`)**: Implementar a relação 1:N onde um curso contém múltiplos módulos.
- [ ] **E-mails e Telefones**: Implementar como arquivos separados ou campos dinâmicos, garantindo que um usuário possa ter múltiplos contatos (Relação 1:N).

## Fase 3: Lógica de Negócio e Matrículas
Integrar as entidades através da funcionalidade principal:
- [ ] **Entidade de Matrícula (`Register`)**: Criar a tabela/arquivo que relaciona um `Student_ID` com um `Module_ID`.
- [ ] **Validações de Matrícula**:
    - Verificar se o aluno já está matriculado no módulo.
    - Validar se o módulo possui um professor atribuído.
    - Garantir integridade referencial (não matricular aluno inexistente).

## Fase 4: Indexação e Performance (AED III)
Para atender aos requisitos de alta performance em arquivos binários:
- [ ] **Índices Primários (Árvore B/B+)**: Implementar um arquivo de índice para permitir busca de IDs em tempo logarítmico, evitando a varredura linear atual.
- [ ] **Índices Secundários**: Implementar índices para busca por Nome ou CPF (ex: Índice Invertido ou Hash).
- [ ] **Cache de Dados**: Implementar um pequeno buffer em memória para os registros acessados mais frequentemente.

## Fase 5: Interface e Robustez
- [ ] **Tratamento de Exceções**: Substituir retornos booleanos simples por um sistema de exceções customizadas para erros de I/O e lógica.
- [ ] **Menu CLI Avançado**: Utilizar uma biblioteca para menus mais interativos ou implementar um sistema de comandos mais fluido.
- [ ] **Logging**: Adicionar um sistema de logs em arquivo para rastrear operações críticas e erros do sistema.

## Fase 6: Verificação e Qualidade
- [ ] **Testes de Integração**: Expandir a pasta `tests/` para cobrir relações entre entidades (ex: testar se ao excluir um curso, o comportamento dos módulos é consistente).
- [ ] **Benchmarks**: Medir o tempo de busca com e sem índices para demonstrar a eficiência da implementação.

---
*Este roadmap é uma sugestão de evolução técnica para o trabalho prático de Algoritmos e Estruturas de Dados III.*
