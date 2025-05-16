ADD jar /opt/cloudera/parcels/CDH/lib/hive/lib/hive-serde.jar;
ADD jar /opt/cloudera/parcels/CDH/lib/hive/lib/hive-contrib.jar;

USE badigulaj;

SELECT request_date, count(distinct  http_status) AS unique_http
from Logs
GROUP BY request_date
ORDER BY unique_http DESC;
