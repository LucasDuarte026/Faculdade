#!/bin/bash

echo  
echo             -- __ -- __ -- __ -- Novo projeto em C -- __ -- __ -- __ --
echo 

cd /mnt/c/Users/micro/OneDrive/Documentos/Faculdade/4º_semestre/shared_facul/ED3

read -p "Nome da pasta do projeto: " FOLDER

mkdir "./$FOLDER"
cd "./$FOLDER"

read -p "Nome do arquivo em C: " FILE

cp -r "/mnt/c/Users/micro/OneDrive/Documentos/Faculdade/4º_semestre/shared_facul/ED3/template_ed3" "./$FOLDER"

code "./$FOLDER"