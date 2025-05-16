ADD jar /opt/cloudera/parcels/CDH/lib/hive/lib/hive-serde.jar;
ADD jar /opt/cloudera/parcels/CDH/lib/hive/lib/hive-contrib.jar;

USE badigulaj;

SELECT 
  ROUND(page_size / 1024.0, 4) AS page_size_mb
FROM Logs
ORDER BY page_size_mb DESC
LIMIT 10;
