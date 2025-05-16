select m.surname, m.firstname, m.memid, min(starttime) starttime
from cd.members m join cd.bookings b on m.memid = b.memid
where b.starttime > '2012-09-01'
group by m.surname, m.firstname, m.memid
order by m.memid
