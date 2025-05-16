select b.firstname, b.surname
from cd.members a join cd.members b
on a.recommendedby = b.memid
group by b.firstname, b.surname
having count(a.memid) > 0
order by b.surname, b.firstname

