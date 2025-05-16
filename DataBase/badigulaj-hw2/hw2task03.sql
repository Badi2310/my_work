with temp_t as (
	select f.facid, extract(month from b.starttime) as month, b.slots
	from cd.facilities f join cd.bookings b
	on f.facid = b.facid
	where extract(year from b.starttime) = 2012
)
select facid, month, sum(slots) total_slots
from temp_t
group by facid, month
order by facid
