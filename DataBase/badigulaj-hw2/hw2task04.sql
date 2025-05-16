with temp_t as (
	select f.facid, extract(month from b.starttime) as month, b.slots
	from cd.facilities f join cd.bookings b
	on f.facid = b.facid
	where extract(year from b.starttime) = 2012
), prev_task as (
	select facid, month, sum(slots) slots
	from temp_t
	group by facid, month
), sum_t as (
	select facid, cast(null as integer) as month, sum(slots) slots
	from temp_t
	group by facid
), total_sum as (select cast(null as integer), cast(null as integer) , sum(slots) from sum_t)

select *
from prev_task
union
select *
from sum_t
union
select *
from total_sum
order by facid, month;
