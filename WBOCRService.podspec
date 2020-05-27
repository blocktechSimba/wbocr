
Pod::Spec.new do |s|
  s.name             = 'WBOCRService'
  s.version          = '3.3.3'
  s.summary          = '博洛科技的OCR私有库'
  s.description      = "ocr SDK"
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Mike' => 'mike@iblocktech.com' }
  s.source           = { :git => "https://github.com/blocktechSimba/wbocr.git" }
  
  s.ios.deployment_target = '9.0'
  s.library = 'c++'
  s.frameworks = "CoreTelephony", "CoreServices", "CoreMedia", "AssetsLibrary","AVFoundation","WebKit","SystemConfiguration"
  
  s.resource_bundles = {
    'WBOCRService' => ['Libs/WBOCRService.bundle/*.png']
  }
  
  s.subspec 'BinaryLib' do |lib|
    lib.vendored_libraries = "Libs/*.a"
    lib.vendored_frameworks = "Libs/*.framework"
  end
  
 
end
