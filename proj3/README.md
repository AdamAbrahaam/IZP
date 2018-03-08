<h1><span><a name="Projekt_3_-_Jednoduchá_shluková_analýza">Projekt 3 - Jednoduchá shluková analýza</a></span></h1>

<h2><span><a name="Popis_projektu">Popis projektu</a></span></h2>

<p>

Vytvořte program, který implementuje jednoduchou shlukovou analýzu, metodu &quot;Unweighted pair-group average&quot; (pouze anglicky).
</p>

<p>

Smyslem projektu není studium shlukových analýz. Pro projekt bude stačit následující popis (zdroj <a href="https://cs.wikipedia.org/wiki/Shlukov%C3%A1_anal%C3%BDza" class="external" title="https://cs.wikipedia.org/wiki/Shlukov%C3%A1_anal%C3%BDza"  rel="nofollow">Wikipedia</a>): <i>Shluková analýza (též clusterová analýza, anglicky cluster analysis) je vícerozměrná statistická metoda, která se používá ke klasifikaci objektů. Slouží k třídění jednotek do skupin (shluků) tak, že jednotky náležící do stejné skupiny jsou si podobnější než objekty z ostatních skupin.</i>
</p>

<p>

Shlukovou analýzu provádějte na dvourozměrných objektech. Každý objekt je identifikován celým číslem. Objekty jsou uloženy v textovém souboru.
</p>

<p>

Při implementaci můžete pro vizualizaci a porozumění objektů používat <a href="http://www.fit.vutbr.cz/study/courses/IZP/public/cluster.php" class="external" title="http://www.fit.vutbr.cz/study/courses/IZP/public/cluster.php"  rel="nofollow">tuto jednoduchou aplikaci</a>, která vykresluje a obarvuje  vámi vygenerované shluky. Reference s popisem metody <a href="https://is.muni.cz/th/172767/fi_b/5739129/web/web/usrov.html" class="external" title="https://is.muni.cz/th/172767/fi_b/5739129/web/web/usrov.html"  rel="nofollow">zde</a>.
</p>

<h2><span><a name="Detailní_specifikace">Detailní specifikace</a></span></h2>

<h3><span><a name="Překlad_a_odevzdání_zdrojového_souboru">Překlad a odevzdání zdrojového souboru</a></span></h3>

<p>

Odevzdání: Program implementujte ve zdrojovém souboru <tt>proj3.c</tt>. Zdrojový soubor odevzdejte prostřednictvím informačního systému.
</p>

<p>

Překlad: Program bude překládán s následujícími argumenty<pre>$ gcc -std=c99 -Wall -Wextra -Werror -DNDEBUG proj3.c -o proj3 -lm</pre>

</p>

<ul>
<li class="level1">Definice makra NDEBUG (argument -DNDEBUG) je z důvodu anulování efektu ladicích informací.</li>
<li class="level1">Propojení s matematickou knihovnou (argument -lm) je z důvodu výpočtu vzdálenosti objektů.</li>
</ul>

<h3><span><a name="Syntax_spuštění">Syntax spuštění</a></span></h3>

<p>

Program se spouští v následující podobě:<pre>./proj3 SOUBOR [N]</pre>

</p>

<p>

Argumenty programu:
</p>

<ul>
<li class="level1"><tt>SOUBOR</tt> je jméno souboru se vstupními daty.</li>
<li class="level1"><tt>N</tt> je volitelný argument definující cílový počet shluků. N &gt; 0. Výchozí hodnota (při absenci argumentu) je 1.</li>
</ul>

<h3><span><a name="Implementační_detaily">Implementační detaily</a></span></h3>

<h4><span><a name="Formát_vstupního_souboru">Formát vstupního souboru</a></span></h4>

<p>

Vstupní data jsou uložena v textovém souboru. První řádek souboru je vyhrazen pro počet objektů v souboru a má formát:<pre>count=N</pre>

kde číslo je počet objektů v souboru. Následuje na každém řádku definice jednoho objektu. Počet řádků souboru odpovídá minimálně počtu objektů + 1 (první řádek). Další řádky souboru ignorujte. Řádek definující objekt je formátu:<pre>OBJID X Y</pre>

kde OBJID je v rámci souboru jednoznačný celočíselný identifikátor, X a Y jsou souřadnice objektu také celá čísla. Platí 0 &lt;= X &lt;= 1000, 0 &lt;= Y &lt;= 1000.
</p>

<h4><span><a name="podúkol">1. podúkol</a></span></h4>

<p>

Stáhněte si kostru programu <a href="/FIT/st/cwk.php?title=IZP:Projekt3&amp;src=Proj3.c&amp;ns=IZP&amp;&amp;action=fileinfo&amp;csid=649642&amp;id=12214" class="media mediafile mf_c" title="proj3.c">proj3.c</a>. Seznamte se s datovými typy a funkcemi. Vaším úkolem je pouze doplnit kód na místech označených komentářem <b>TODO</b>.
</p>

<h4><span><a name="podúkol1">2. podúkol</a></span></h4>

<p>

Načítání vstupního souboru a následný výpis:
</p>

<p>

1. Implementujte funkce:
<div class="c syntax" style="font-family:monospace;"><pre style="font: normal normal 1em/1.2em monospace; margin:0; padding:0; background:none; vertical-align:top;"><span style="color: #993333;">void</span> init_cluster<span style="color: #009900;">&#40;</span><span style="color: #993333;">struct</span> cluster_t <span style="color: #339933;">*</span>c<span style="color: #339933;">,</span> <span style="color: #993333;">int</span> cap<span style="color: #009900;">&#41;</span><span style="color: #339933;">;</span>
<span style="color: #993333;">void</span> clear_cluster<span style="color: #009900;">&#40;</span><span style="color: #993333;">struct</span> cluster_t <span style="color: #339933;">*</span>c<span style="color: #009900;">&#41;</span><span style="color: #339933;">;</span>
<span style="color: #993333;">void</span> append_cluster<span style="color: #009900;">&#40;</span><span style="color: #993333;">struct</span> cluster_t <span style="color: #339933;">*</span>c<span style="color: #339933;">,</span> <span style="color: #993333;">struct</span> obj_t obj<span style="color: #009900;">&#41;</span><span style="color: #339933;">;</span>
<span style="color: #993333;">int</span> load_clusters<span style="color: #009900;">&#40;</span><span style="color: #993333;">char</span> <span style="color: #339933;">*</span>filename<span style="color: #339933;">,</span> <span style="color: #993333;">struct</span> cluster_t <span style="color: #339933;">**</span>arr<span style="color: #009900;">&#41;</span><span style="color: #339933;">;</span></pre></div>
</p>

<p>

Funkce <tt>init_cluster</tt> slouží pro inicializaci shluku (alokaci požadovaného místa).
</p>

<p>

Funkce <tt>clear_cluster</tt> slouží pro odstranění všech objektů ve shluku (dealokaci místa) a reinicializaci shluku s kapacitou 0.
</p>

<p>

Funkce <tt>append_cluster</tt> slouží pro přidání objektu na konec shluku.
</p>

<p>

Funkce <tt>load_clusters</tt> načítá ze vstupního souboru všechny objekty a ukládá je každý do jednoho shluku. Shluky budou uloženy v poli. Místo pro pole shluků musí funkce alokovat.
</p>

<p>

2. Ověřte funkcionalitu na načtení vstupního souboru (pomocí vámi implementované funkce <tt>load_clusters</tt>) a následném výpisu (pomocí funkce <tt>print_clusters</tt>):
</p>

<p>

Vstupní soubor <tt>objekty</tt><pre>count=20
40 86 663
43 747 938
47 285 973
49 548 422
52 741 541
56 44 854
57 795 59
61 267 375
62 85 874
66 125 211
68 80 770
72 277 272
74 222 444
75 28 603
79 926 463
83 603 68
86 238 650
87 149 304
89 749 190
93 944 835</pre>

</p>

<p>

Načtení vstupního souboru a následné vypsání shluků:<pre>$ ./proj3 objekty 20
Clusters:
cluster 0: 40[86,663]
cluster 1: 43[747,938]
cluster 2: 47[285,973]
cluster 3: 49[548,422]
cluster 4: 52[741,541]
cluster 5: 56[44,854]
cluster 6: 57[795,59]
cluster 7: 61[267,375]
cluster 8: 62[85,874]
cluster 9: 66[125,211]
cluster 10: 68[80,770]
cluster 11: 72[277,272]
cluster 12: 74[222,444]
cluster 13: 75[28,603]
cluster 14: 79[926,463]
cluster 15: 83[603,68]
cluster 16: 86[238,650]
cluster 17: 87[149,304]
cluster 18: 89[749,190]
cluster 19: 93[944,835]</pre>

</p>

<h4><span><a name="podúkol2">3. podúkol</a></span></h4>

<p>

Implementujte všechny ostatní funkce v kostře souboru <a href="/FIT/st/cwk.php?title=IZP:Projekt3&amp;src=Proj3.c&amp;ns=IZP&amp;&amp;action=fileinfo&amp;csid=649642&amp;id=12214" class="media mediafile mf_c" title="proj3.c">proj3.c</a> označené komentářem TODO. Výsledný program odevzdejte.
</p>

<h3><span><a name="Příklady_vstupů_a_výstupů">Příklady vstupů a výstupů</a></span></h3>

<p>
<pre>$ cat objekty
count=20
40 86 663
43 747 938
47 285 973
49 548 422
52 741 541
56 44 854
57 795 59
61 267 375
62 85 874
66 125 211
68 80 770
72 277 272
74 222 444
75 28 603
79 926 463
83 603 68
86 238 650
87 149 304
89 749 190
93 944 835</pre>

</p>

<p>
<pre>$ ./proj3 objekty 8
Clusters:
cluster 0: 40[86,663] 56[44,854] 62[85,874] 68[80,770] 75[28,603] 86[238,650]
cluster 1: 43[747,938]
cluster 2: 47[285,973]
cluster 3: 49[548,422]
cluster 4: 52[741,541] 79[926,463]
cluster 5: 57[795,59] 83[603,68] 89[749,190]
cluster 6: 61[267,375] 66[125,211] 72[277,272] 74[222,444] 87[149,304]
cluster 7: 93[944,835]</pre>

</p>

<p>
<pre>$ valgrind ./proj3 objekty 19
==8650== Memcheck, a memory error detector
==8650== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==8650== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==8650== Command: ./proj3 obj_ex 19
==8650== 
Clusters:
cluster 0: 40[86,663]
cluster 1: 43[747,938]
cluster 2: 47[285,973]
cluster 3: 49[548,422]
cluster 4: 52[741,541]
cluster 5: 56[44,854] 62[85,874]
cluster 6: 57[795,59]
cluster 7: 61[267,375]
cluster 8: 66[125,211]
cluster 9: 68[80,770]
cluster 10: 72[277,272]
cluster 11: 74[222,444]
cluster 12: 75[28,603]
cluster 13: 79[926,463]
cluster 14: 83[603,68]
cluster 15: 86[238,650]
cluster 16: 87[149,304]
cluster 17: 89[749,190]
cluster 18: 93[944,835]
==8650== 
==8650== HEAP SUMMARY:
==8650==     in use at exit: 0 bytes in 0 blocks
==8650==   total heap usage: 25 allocs, 25 frees, 9,328 bytes allocated
==8650== 
==8650== All heap blocks were freed -- no leaks are possible
==8650== 
==8650== For counts of detected and suppressed errors, rerun with: -v
==8650== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)</pre>

</p>

<h4><span><a name="Poznámka_k_2017-12-08">Poznámka k 2017-12-08</a></span></h4>

<p>

Nástroj valgrind na stroji merlin nebo eva může poskytovat falešná varování (upozorňuje na chybu, která ve skutečnosti chybou není). Z toho důvodu je doporučené zkoumat programy na stroji eva s následujícími parametry:<pre>
valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp ./proj3 objekty 19</pre>

</p>

<p>

K tomuto potřebujete mít ve stejném adresáři soubor valgrind.supp s následujícím obsahem:
</p>

<p>
<pre>{
   glibc merlin cond
   Memcheck:Cond
   ...
   obj:/usr/*/ld-*
}
{
   glibc merlin leak
   Memcheck:Leak
   ...
   obj:/usr/*/ld-*
}
{
   libc eva leak
   Memcheck:Leak
   ...
   obj:/lib/libc.so.7
}</pre>

</p>

<p>

Na serveru eva je jiný operační systém než na merlin, a proto je třeba zdrojový soubor přeložit na stroji eva.
</p>

<h2><span><a name="Hodnocení">Hodnocení</a></span></h2>

<p>

Na výsledném hodnocení mají hlavní vliv následující faktory:
</p>

<ul>
<li class="level1">přesné dodržení implementačních detailů,</li>
<li class="level1">implementace jednotlivých funkcí,</li>
<li class="level1">správná práce s pamětí,</li>
<li class="level1">správný algoritmus shlukování,</li>
<li class="level1">správné řešení neočekávaných stavů.</li>
</ul>

<h2><span><a name="Prémiové_řešení">Prémiové řešení</a></span></h2>

<p>

V případě správného řešení projektu můžete získat až 2 prémiové body. Prémiové řešení spočívá v implementaci dalších shlukovacích metod, konkrétně hledání podle nejbližšího souseda a nejvzdálenějšího souseda. Volba metody je dána třetím argumentem programu a to:
</p>

<p>
<pre>./proj3 SOUBOR N [METHOD]</pre>

</p>

<p>

Kde <tt>METHOD</tt> je volitelný argument:
</p>

<ul>
<li class="level1"><tt>--avg</tt> specifikuje metodu &quot;Unweighted pair-group average&quot; (výchozí),</li>
<li class="level1"><tt>--min</tt> speficikuje metodu nejbližšího souseda,</li>
<li class="level1"><tt>--max</tt> speficikuje metodu nejvzdálenějšího souseda.</li>
</ul>

<p>

Rozšíření projektu implementujte ve funkci <tt>cluster_distance</tt>. Prototyp funkce neměňte. Pro účely nastavení metody je povoleno použít jednu globální proměnnou s identifikátorem <tt>premium_case</tt>.
</p>
