with reduced_bookings as (
	select *
	from cd.bookings b
	where date(starttime) = '2012-09-14'
), cost_bookings as (
	select *,
		case
			when memid = 0 then slots * (select guestcost from cd.facilities f where f.facid = rb.facid)
			else slots * (select membercost from cd. facilities f where f.facid = rb.facid)
		end as cost
	from reduced_bookings rb
), names_bookings as (
	select *,
		(select concat(m.firstname, ' ', m.surname) from cd.members m where m.memid = cb.memid) as "member",
		(select f.name from cd.facilities f where f.facid = cb.facid) as facility
	from cost_bookings cb
)
select member, facility, cost
from names_bookings
where cost > 30
order by cost desc, member, facility
