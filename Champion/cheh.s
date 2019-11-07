.name "Cheh"
.comment "30mn mieux que 2 mois"

lfork %2048
		sti r1, %:live, %1
		and r1, %0, r1
live:	live %1
		zjmp %:live
