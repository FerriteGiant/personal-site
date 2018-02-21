rm -r ./public/
hugo
cp -r ./public/* /var/www/chrisgreenley.com/public_html/
sudo chgrp -R www-data /var/www/chrisgreenley.com/public_html/
chmod -R 750 /var/www/chrisgreenley.com/public_html/
