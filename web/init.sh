#!/bin/bash

RESOURCE_GROUP="flask-rg"
APP_NAME="ps2-web"
LOCATION="westeurope"
PLAN_NAME="flask-plan"
ZIP_FILE="ps2_web.zip"

pip freeze > requirements.txt
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

az webapp deploy \
  --resource-group $RESOURCE_GROUP \
  --name $APP_NAME \
  --src-path $ZIP_FILE \
  --type zip

echo "Deployed! Visit: https://$APP_NAME.azurewebsites.net"