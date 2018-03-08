/**
 *@file
 */

/*
 * Soubor:  proj3.h
 *
 *	VUT FIT
 *	IZP 2017/2018
 *	Projekt 3 - Jednoduchá shluková analýza
 *	Autor: Adam Abrahám
 *	Datum: 10.12.2017
 *
 *
 * Kostra hlavickoveho souboru 3. projekt IZP 2017/18
 * a pro dokumentaci Javadoc. 
 */

/**
 * \defgroup Struktury Pouzite struktury
 * @{
 */
 
/**
 * @brief Struktura jedneho objektu.
 */
struct obj_t {
	///Identifikacne cislo objektu.
    int id;
	///X-ova suradnica objektu.
    float x;
	///Y-ova suradnica objektu.
    float y;
};

/**
 * @brief Struktura zhluku.
 */
struct cluster_t {
	///Pocet objektov v zhluku.
    int size;
	///Pocet objektov kolko sa zmesti do zhluku.
    int capacity;
	///Ukazovatel na pole objektov.
    struct obj_t *obj;
};
/** @} */

/** 
 * \defgroup Konstanta Pouzite konstanty
 * @{
 */
 
/**
 * @brief Konstanta potrebna pre realokaciu. 
 */
extern const int CLUSTER_CHUNK;
/**
 * @}
 */
 
/**
 * \defgroup Funkcie Pouzite funkcie
 * @{
 */

/**
 * @brief Inicializuje zhluk a alokuje pamat pre kapacitu objektov.
 * 
 * @pre C nemoze byt NULL, CAP musi byt vacsia ako 0
 * @post C ukazuje na adresu prveho prvku v poli zhlukov
 *
 * @param c Ukzovatel na zhluk
 * @param cap Kapacita
 */ 
void init_cluster(struct cluster_t *c, int cap);

/**
 * @brief Odstrani vsetky objekty zhluku.
 * 
 * @pre C nemoze byt NULL.
 * @post Pamat je uvolnena.
 *
 * @param c Ukzovatel na zhluk.
 */ 
void clear_cluster(struct cluster_t *c);

/**
 * @brief Zmeni kapacitu zhluku 'c' na novu kapacitu.
 * 
 * @pre C nemoze byt NULL, NEW_CAP musi byt vacsia ako 0
 * @post Nova kapacita
 *
 * @param c Ukzovatel na zhluk
 * @param new_cap Nova kapacita
 *
 * @return Vrati ukazovatel na zhluk s novou kapacitou.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);

/**
 * @brief Prida objekt na koniec zhluku.
 * 
 * @pre C nemoze byt NULL
 * @post Objekt je pridany na koniec zhluku.
 *
 * @param c Ukzovatel na zhluk
 * @param obj Objekt, ktory sa pridava.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj);

/**
 * @brief Prida objekty z jedneho zhluku do druheho a zavola funkciu 'sort_cluster'.
 * 
 * @pre C1 a C2 nemozu byt NULL
 * @post Objekty zo zhluku C2 su pridane do zhluku C1.
 *
 * @param c1 Ukazovatel na zhluk 1
 * @param c2 Ukazovatel na zhluk 2
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);

/**
 * @brief Odstrani zhluk z pola zhlukov.
 * 
 * @pre Idx musi byt mensi ako narr, narr musi byt vacsi ako 0
 * @post Zhluk je odstraneny z pola zhlukov.
 *
 * @param carr Ukazovatel na prvu polozku.
 * @param narr Pocet zhlukov v poli
 * @param idx Index na zhluk
 *
 * @return Novy pocet zhlukov v poli zhlukov.
 */
int remove_cluster(struct cluster_t *carr, int narr, int idx);

/**
 * @brief Vypocita vzdialenost medzi objektami.
 * 
 * @pre O1 a O2 nemozu byt NULL.
 * @post Vzdialenost je vypocitana.
 *
 * @param o1 Ukzovatel na prvy objekt.
 * @param o2 Ukazovatel na druhy objekt.
 *
 * @return Vracia vzdialenost medzi objektami. 
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2);

/**
 * @brief Vypocita vzdialenost dvoch zhlukov.
 * 
 * @pre C1 a C2 nemozu byt NULL.
 * @post Vzdialenost je vypocitana.
 *
 * @param c1 Ukazovatel na prvy zhluk.
 * @param c2 Ukazovatel na druhy zhluk.
 *
 * @return Vracia vzdialenost dvoch zhlukov.
 */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);

/**
 * @brief Hlada dva najblizsie zhluky.
 * 
 * @pre CARR nemoze byt NULL, narr musi byt vacsi ako 0.
 * @post Nasli sa dva najblizsie zhluky.
 *
 * @param carr Ukazovatel na prvu polozku.
 * @param narr Pocet zhlukov v poli.
 * @param c1 Ukazovatel na index prveho zhluku z dvojice.
 * @param c2 Ukazovatel na index druheho zhluku z dvojice.
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);

/**
 * @brief Zoradi objekty v zhluku podla ID.
 * 
 * @pre C nemoze byt NULL.
 * @post Objekty su zoradene podla ID.
 *
 * @param c Ukzovatel na zhluk
 */
void sort_cluster(struct cluster_t *c);

/**
 * @brief Vypise vsetky objekty zo zhluku.
 * 
 * @pre C nemoze byt NULL.
 * @post Objekty su vypisane.
 *
 * @param c Ukzovatel na zhluk
 */
void print_cluster(struct cluster_t *c);

/**
 * @brief Nacita objekty zo suboru, ulozi ich do zhlukov a zhluky do pola.
 * 
 * @pre arr nemoze byt NULL, subor musi existovat.
 * @post *arr obsahuje ukazatel na prvy prvok zhluku.
 *
 * @param filename Meno suboru.
 * @param arr Ukazatel na ukazatel na pole zhlukov.
 *
 * @return Vrati pocet nacitanych objektov (zhlukov).
 */
int load_clusters(char *filename, struct cluster_t **arr);

/**
 * @brief Vypise pole zhlukov.
 * 
 * @pre CARR nemoze byt NULL, narr musi byt vacsi ako 0.
 * @post Zhluky su vypisane.
 *
 * @param carr Ukzovatel na prvu polozku.
 * @param narr Pocet zhlukov v poli.
 */
void print_clusters(struct cluster_t *carr, int narr);
 /** @} */