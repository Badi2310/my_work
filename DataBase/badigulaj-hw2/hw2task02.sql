select b.memid recommendedby, count(a.memid) count
from cd.members a join cd.members b
on a.recommendedby = b.memid
group by b.memid
having count(a.memid) > 0
order by recommendedby
