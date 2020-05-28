
Pod::Spec.new do |s|
  s.name             = 'WBOCRService'
  s.version          = '3.3.3'
  s.summary          = '博洛科技的OCR私有库'
  s.description      = "ocr SDK"
  s.homepage         = "https://github.com/blocktechSimba/wbocr/tree/master"
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Mike' => 'mike@iblocktech.com' }
  s.source           = { :git => "https://ae03d56644925695064c89ca184421a43408ae32@github.com/blocktechSimba/wbocr.git" }
  
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
