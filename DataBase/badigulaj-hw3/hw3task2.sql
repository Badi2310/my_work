select count(memid) over(), m.firstname , m.surname 
from cd.members m
group by memid
order by joindate
