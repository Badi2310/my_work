ADD jar /opt/cloudera/parcels/CDH/lib/hive/lib/hive-contrib.jar;

USE badigulaj;

SELECT TRANSFORM ( ip, request_date, request, page_size, http_status, info)
USING 'sed "s/http/ftp/"'
FROM Logs
LIMIT 10;
