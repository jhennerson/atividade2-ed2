typedef struct NoAVL *arvAVL;

int maior(int x, int y);
int alt_no(struct NoAVL *no);
int vazia_arvAVL(arvAVL *raiz);
int altura_arvAVL(arvAVL *raiz);
int totalNoAVL_arvAVL(arvAVL *raiz);
int fatorBalanceamento_NoAVL(struct NoAVL *no);
int remove_arvAVL(arvAVL *raiz, int cod);
int insere_arvAVL(arvAVL *raiz, Pessoa p);
int consulta_arvAVL(arvAVL *raiz, int cod);

void rotacaoLL(arvAVL *raiz);
void rotacaoRR(arvAVL *raiz);
void rotacaoLR(arvAVL *raiz);
void rotacaoRL(arvAVL *raiz);
void libera_arvAVL(arvAVL *raiz);
void emOrdem_arvAVL(arvAVL *raiz);
void preOrdem_arvAVL(arvAVL *raiz);
void posOrdem_arvAVL(arvAVL *raiz);

struct NoAVL *procuramenor(struct NoAVL *atual);
