select a.firstname memfname,
	   a.surname memsname,
	   b.firstname recfname,
	   b.surname recsname
from cd.members a left join cd.members b
on a.recommendedby = b.memid
order by a.surname, a.firstname
