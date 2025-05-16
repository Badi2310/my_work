select name,
	case 
		when ntile(3) over w = 3 then 'high'
		when ntile(3) over w = 2 then 'average'
		when ntile(3) over w = 1 then 'low'
	end as revenue
from cd.facilities f
window w as (order by f.monthlymaintenance)
order by ntile(3) over w desc, name;
