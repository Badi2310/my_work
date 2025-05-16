select name,
	case 
		when monthlymaintenance > 100 then 'expensive'
		else 'cheap'
	end cost
from cd.facilities
