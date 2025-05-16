select concat(a.firstname, ' ', a.surname) member,
	(select concat(b.firstname, ' ', b.surname) from cd.members b where a.recommendedby = b.memid) recommender
from cd.members a
order by member;
