typedef struct NoLLRB *arvLLRB;

int vazia_arvLLRB(arvLLRB *raiz);
int altura_arvLLRB(arvLLRB *raiz);
int totalNoLLRB_arvLLRB(arvLLRB *raiz);
void libera_arvLLRB(arvLLRB *raiz);
int remove_arvLLRB(arvLLRB *raiz, int cod);
int insere_arvLLRB(arvLLRB *raiz, Pessoa p);
int consulta_arvLLRB(arvLLRB *raiz, int cod);

void preOrdem_arvLLRB(arvLLRB *raiz);
void emOrdem_arvLLRB(arvLLRB *raiz);
void posOrdem_arvLLRB(arvLLRB *raiz);

struct NoLLRB *remove_atual(struct NoLLRB *atual);
struct NoLLRB *removeNoLLRB(struct NoLLRB *H, int cod);
struct NoLLRB *removeNoLLRB(struct NoLLRB *H, int cod);
struct NoLLRB *insereNoLLRB(struct NoLLRB *H, Pessoa p, int *resp);
