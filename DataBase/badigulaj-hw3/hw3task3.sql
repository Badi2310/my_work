select m.firstname, m.surname, round(sum(b.slots) / 2, -1) as hours, rank() over(order by round(sum(b.slots) / 2, -1) desc) as rank
from cd.members m join cd.bookings b
on m.memid = b.memid
group by m.memid
order by rank, m.surname, m.firstname
