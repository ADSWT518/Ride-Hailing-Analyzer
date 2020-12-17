#include "dataForm.h"

orderDataForm::orderDataForm(QStringList lst)
{
    order_id = lst[0].trimmed();
    departure_time = lst[1].trimmed().toUInt();
    end_time = lst[2].trimmed().toUInt();
    orig_lng = lst[3].trimmed().toDouble();
    orig_lat = lst[4].trimmed().toDouble();
    dest_lng = lst[5].trimmed().toDouble();
    dest_lat = lst[6].trimmed().toDouble();
    fee = lst[7].trimmed().toDouble();
}

gridDataForm::gridDataForm(QStringList lst)
{
    grid_id = lst[0].trimmed().toUInt();
    vertex0_lng = lst[1].trimmed().toDouble();
    vertex0_lat = lst[2].trimmed().toDouble();
    vertex1_lng = lst[3].trimmed().toDouble();
    vertex1_lat = lst[4].trimmed().toDouble();
    vertex2_lng = lst[5].trimmed().toDouble();
    vertex2_lat = lst[6].trimmed().toDouble();
    vertex3_lng = lst[7].trimmed().toDouble();
    vertex3_lat = lst[8].trimmed().toDouble();
}