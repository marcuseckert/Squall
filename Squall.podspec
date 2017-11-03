#
# Be sure to run `pod lib lint Squall.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = "Squall"
  s.version          = "2.462"
  s.summary          = "Squall  - After Effects to iOS."
  s.ios.deployment_target = "8.0"
  s.platform     = :ios, '8.0'
  s.description      = "Squall  - convert After Effects animations to iOS code and integrate them with your app."

  s.homepage         = "https://github.com/marcuseckert/Squall"
  s.license = { :type => 'Commercial', :file => 'LICENSE' }
  s.author           = { "Forge and Form GmbH" => "hello@squall.no" }
  s.source           = { :git => "https://github.com/marcuseckert/Squall.git", :tag => s.version.to_s }
  s.social_media_url = 'https://twitter.com/marcus_eckert'

  
  s.resource_bundles = {
    'Squall' => ['Squall.framework/rsaCert.der', 'Squall.framework/squallLicense.pdf']
  }
  s.xcconfig       = { 'FRAMEWORK_SEARCH_PATHS' => '"$(PODS_ROOT)/Squall"' }
  s.preserve_paths = 'Squall.framework'
  s.source_files = 'Squall.framework/Headers/**/*.h'  
  s.public_header_files = 'Squall.framework/Headers/**/*.h'
  s.frameworks = 'UIKit', 'QuartzCore'
  s.ios.vendored_frameworks = 'Squall.framework'
  s.requires_arc = true
  

end
