select distinct concat(firstname, ' ', surname) member, f.name facility
from cd.members m
left join cd.bookings b on m.memid = b.memid
left join cd.facilities f on b.facid = f.facid
where position('Tennis Court' in f.name) != 0 
order by member, facility
