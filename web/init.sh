#!/bin/bash

RESOURCE_GROUP="flask"
APP_NAME="ps2-web"
LOCATION="westeurope"
PLAN_NAME="flask-plan"
ZIP_FILE="ps2_web.zip"

if [ "$1" = "deploy" ];
then
	python3 -m pip freeze > requirements.txt
	zip -r $ZIP_FILE .

	az group create --name $RESOURCE_GROUP --location $LOCATION

	az appservice plan create \
	  --name $PLAN_NAME \
	  --resource-group $RESOURCE_GROUP \
	  --sku B1 \
	  --is-linux

	az webapp create \
	  --resource-group $RESOURCE_GROUP \
	  --plan $PLAN_NAME \
	  --name $APP_NAME \
	  --runtime "PYTHON|3.10"

	az webapp config set \
	  --resource-group $RESOURCE_GROUP \
	  --name $APP_NAME \
	  --startup-file "gunicorn app:app --bind=0.0.0.0 --workers=1"

	az webapp deploy \
	  --resource-group $RESOURCE_GROUP \
	  --name $APP_NAME \
	  --src-path $ZIP_FILE \
	  --type zip

	echo "Deployed! Visit: https://$APP_NAME.azurewebsites.net"
	
elif [ "$1" = "start" ];
then
	az webapp start --name $APP_NAME --resource-group $RESOURCE_GROUP
	
elif [ "$1" = "close" ];
then
	az webapp stop --name $APP_NAME --resource-group $RESOURCE_GROUP

else
	echo "./init.sh deploy|start|close"

fi
