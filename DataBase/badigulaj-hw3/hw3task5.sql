with
	facilities_incomes as (
		select
			f.name,
			sum(
				case 
					when m.firstname = 'GUEST' then b.slots * f.guestcost
					else b.slots * f.membercost
				end 
				) as income
		from cd.members m 
		right join cd.bookings b on m.memid = b.memid
		left join cd.facilities f on b.facid = f.facid
		group by f.name
		order by income desc
	)
select
	fi.name,
	rank() over(order by income desc)
from facilities_incomes fi 
order by rank, fi.name
limit 3;
