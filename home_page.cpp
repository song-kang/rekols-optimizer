#include "home_page.h"
#include "utils.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout();
    bottomLayout = new QHBoxLayout();
    infoLayout = new QVBoxLayout();
    networkLayout = new QVBoxLayout();
    systemInfo = new QLabel("SYSTEM INFO");
    hostName = new QLabel("Hostname: ");
    platform = new QLabel("Platform: ");
    distribution = new QLabel("Distribution: ");
    kernel = new QLabel("Kernel Release: ");
    cpuModel = new QLabel("Cpu Model: ");
    cpuCoreCount = new QLabel("Cpu Core: ");

    uploadInfo = new QLabel("UPLOAD");
    downloadInfo = new QLabel("DOWNLOAD");
    uploadLabel = new QLabel("↑ 0.0 B/s");
    downloadLabel = new QLabel("↓ 0.0 B/s");

    thread = new Thread();
    cpuMonitor = new CPUMonitor();
    memoryMonitor = new MemoryMonitor();
    diskMonitor = new DiskMonitor();

    systemInfo->setStyleSheet("color: #4088C6");
    uploadInfo->setStyleSheet("color: #31A38C");
    downloadInfo->setStyleSheet("color: #C45045");

    QFont font;
    font.setPointSize(18);
    systemInfo->setFont(font);
    uploadInfo->setFont(font);
    downloadInfo->setFont(font);

    topLayout->addSpacing(15);
    topLayout->addWidget(cpuMonitor);
    topLayout->addWidget(memoryMonitor);
    topLayout->addWidget(diskMonitor);
    topLayout->addSpacing(15);

    bottomLayout->addSpacing(25);
    bottomLayout->addLayout(infoLayout);
    bottomLayout->addLayout(networkLayout);
    bottomLayout->addSpacing(25);

    infoLayout->addStretch();
    infoLayout->addWidget(systemInfo);
    infoLayout->addSpacing(5);
    infoLayout->addWidget(hostName);
    infoLayout->addWidget(platform);
    infoLayout->addWidget(distribution);
    infoLayout->addWidget(kernel);
    infoLayout->addWidget(cpuModel);
    infoLayout->addWidget(cpuCoreCount);
    infoLayout->addStretch();

    networkLayout->addWidget(uploadInfo);
    networkLayout->addSpacing(5);
    networkLayout->addWidget(uploadLabel);
    networkLayout->addSpacing(20);
    networkLayout->addWidget(downloadInfo);
    networkLayout->addSpacing(5);
    networkLayout->addWidget(downloadLabel);
    networkLayout->addStretch();

    layout->addStretch();
    layout->addLayout(topLayout);
    layout->addStretch();
    layout->addLayout(bottomLayout);
    layout->addStretch();

    hostName->setText("HostName: " + Utils::getUserName());
    platform->setText("Platform: " + Utils::getPlatform());
    distribution->setText("Distribution: " + Utils::getDistribution());
    kernel->setText("Kernel Release: " + Utils::getKernel());
    cpuModel->setText("Cpu Model: " + Utils::getCpuModel());
    cpuCoreCount->setText("Cpu Core: " + Utils::getCpuCoreCount());

    thread->start();

    connect(thread, &Thread::updateCpuPercent, this, &HomePage::updateCpuPercent);
    connect(thread, &Thread::updateMemoryPercent, this, &HomePage::updateMemoryPercent);
    connect(thread, &Thread::updateMemory, this, &HomePage::updateMemory);
    connect(thread, &Thread::updateDiskPercent, this, &HomePage::updateDiskPercent);
    connect(thread, &Thread::updateDisk, this, &HomePage::updateDisk);
    connect(thread, &Thread::updateNetworkSpeed, this, &HomePage::updateNetworkSpeed);
}

void HomePage::updateCpuPercent(int cpuPercent)
{
    cpuMonitor->setPercentValue(cpuPercent);
}

void HomePage::updateMemoryPercent(int memoryPercent)
{
    memoryMonitor->setPercentValue(memoryPercent);
}

void HomePage::updateMemory(QString memory)
{
    memoryMonitor->setMemoryInfo(memory);
}

void HomePage::updateDiskPercent(int diskPercent)
{
    diskMonitor->setPercentValue(diskPercent);
}

void HomePage::updateDisk(QString disk)
{
    diskMonitor->setDiskInfo(disk);
}

void HomePage::updateNetworkSpeed(QString upload, QString download)
{
    uploadLabel->setText(upload);
    downloadLabel->setText(download);
}
